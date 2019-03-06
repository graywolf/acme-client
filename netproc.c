/*	$Id: netproc.c,v 1.22 2019/02/01 10:16:04 benno Exp $ */
/*
 * Copyright (c) 2016 Kristaps Dzonsons <kristaps@bsd.lv>
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHORS DISCLAIM ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#include <assert.h>
#include <ctype.h>
#include <err.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <curl/curl.h>

#include "compat.h"
#include "extern.h"
#include "parse.h"

#define	RETRY_DELAY 5
#define RETRY_MAX 10

/*
 * Buffer used when collecting the results of a CURL transfer.
 */
struct	buf {
	char	*buf; /* binary buffer */
	size_t	 sz; /* length of buffer */
};

/*
 * Used for CURL communications.
 */
struct	conn {
	const char	  *na; /* nonce authority */
	int		   fd; /* acctproc handle */
	int		   dfd; /* dnsproc handle */
	struct buf	   buf; /* transfer buffer */
};

/*
 * If something goes wrong (or we're tracing output), we dump the
 * current transfer's data as a debug message.
 * Make sure that print all non-printable characters as question marks
 * so that we don't spam the console.
 * Also, consolidate white-space.
 * This of course will ruin string literals, but the intent here is just
 * to show the message, not to replicate it.
 */
static void
buf_dump(const struct buf *buf)
{
	size_t	 i;
	int	 j;
	char	*nbuf;

	if (buf->sz == 0)
		return;
	if ((nbuf = malloc(buf->sz)) == NULL)
		err(EXIT_FAILURE, "malloc");

	for (j = 0, i = 0; i < buf->sz; i++)
		if (isspace((int)buf->buf[i])) {
			nbuf[j++] = ' ';
			while (isspace((int)buf->buf[i]))
				i++;
			i--;
		} else
			nbuf[j++] = isprint((int)buf->buf[i]) ?
			    buf->buf[i] : '?';
	dodbg("transfer buffer: [%.*s] (%zu bytes)", j, nbuf, buf->sz);
	free(nbuf);
}

static size_t write_cb(char *ptr, size_t size, size_t nmemb, void *userdata) {
	(void)size; /* always 1 */

	struct buf *buf = (struct buf *)userdata;
	char *new_buf = NULL;

	if (buf->buf) {
		new_buf = recallocarray(buf->buf, buf->sz, buf->sz + nmemb, 1);
	} else {
		new_buf = calloc(nmemb, 1);
	}
	if (!new_buf) { return 0; }
	buf->buf = new_buf;

	memcpy(buf->buf + buf->sz, ptr, nmemb);
	buf->sz += nmemb;

	return nmemb;
}

static CURL *prepare_curl(char const *addr, struct buf *buf) {
	CURL *curl = curl_easy_init();
	if (!curl) { return curl; }

	curl_easy_setopt(curl, CURLOPT_URL, addr);
	curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
	curl_easy_setopt(curl, CURLOPT_MAXREDIRS, 3L);
	curl_easy_setopt(curl, CURLOPT_SSLVERSION, CURL_SSLVERSION_TLSv1_2);

	if (buf) {
		free(buf->buf);
		buf->sz = 0;
		buf->buf = NULL;

		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_cb);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, buf);
	}
	/* TODO: swallow the answer if buf not provided */

	return curl;
}

/*
 * Send a "regular" HTTP GET message to "addr" and stuff the response
 * into the connection buffer.
 * Return the HTTP error code or <0 on failure.
 */
static long
nreq(struct conn *c, const char *addr)
{
	long code;
	CURL *curl = NULL;

	curl = prepare_curl(addr, &c->buf);
	if (!curl) {
		return -1;
	}

	if (curl_easy_perform(curl) != CURLE_OK) {
		curl_easy_cleanup(curl);
		return -1;
	}

	curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &code);

	curl_easy_cleanup(curl);
	return code;
}

static size_t
get_nonce_cb(char *buf, size_t size, size_t nitems, void *userdata) {
	char **nonce = (char **)userdata;
	char *name = NULL;
	char *value = NULL;
	size_t buf_len = size * nitems;
	size_t processed = buf_len;

	char *colon_ptr = memchr(buf, ':', buf_len);
	if (!colon_ptr) {
		/* Not a valid header line. Either something like `HTTP/2 200`
		 * or folded header, which this parsing does not support. */
		return buf_len;
	}

	name = strndup(buf, colon_ptr - buf);
	if (!name) {
		warnx("strndup for name");
		processed = 0;
		goto out;
	}

	for (++colon_ptr; isspace(*colon_ptr); ++colon_ptr) ;
	char *val_start = colon_ptr;
	size_t val_len = buf + buf_len - 1 - val_start;
	for (; isspace(val_start[val_len - 1]); --val_len) ;

	value = strndup(val_start, val_len);
	if (!value) {
		warnx("strndup for value");
		processed = 0;
		goto out;
	}

	/* Http headers are defined to be case insensitive. */
	for (char *p = name ; *p; ++p) { *p = tolower(*p); }

	if (strcmp("replay-nonce", name) == 0) {
		if (*nonce) {
			warnx("multiple replay-nonce");
			processed = 0;
			goto out;
		}
		*nonce = value;
		value = NULL;
	}

out:
	free(name);
	free(value);
	return processed;
}

/*
 * Create and send a signed communication to the ACME server.
 * Stuff the response into the communication buffer.
 * Return <0 on failure on the HTTP error code otherwise.
 */
static long
sreq(struct conn *c, const char *addr, const char *req)
{
	CURL *curl = NULL;
	long code = 0;
	char *nonce = NULL;
	char *reqsn = NULL;

	curl = prepare_curl(addr, NULL);
	if (!curl) { return -1; }

	curl_easy_setopt(curl, CURLOPT_HEADERFUNCTION, get_nonce_cb);
	curl_easy_setopt(curl, CURLOPT_HEADERDATA, &nonce);

	if (curl_easy_perform(curl) != CURLE_OK) {
		curl_easy_cleanup(curl);
		return -1;
	}
	curl_easy_cleanup(curl);

	if (!nonce) {
		warnx("%s: no replay nonce", c->na);
		return -1;
	}

	/*
	 * Send the nonce and request payload to the acctproc.
	 * This will create the proper JSON object we need.
	 */
	if (writeop(c->fd, COMM_ACCT, ACCT_SIGN) <= 0) {
		free(nonce);
		return -1;
	} else if (writestr(c->fd, COMM_PAY, req) <= 0) {
		free(nonce);
		return -1;
	} else if (writestr(c->fd, COMM_NONCE, nonce) <= 0) {
		free(nonce);
		return -1;
	}
	free(nonce);

	/* Now read back the signed payload. */
	if ((reqsn = readstr(c->fd, COMM_REQ)) == NULL)
		return -1;

	curl = prepare_curl(addr, &c->buf);
	if (!curl) {
		return -1;
	}

	curl_easy_setopt(curl, CURLOPT_POSTFIELDS, reqsn);

	if (curl_easy_perform(curl) != CURLE_OK) {
		curl_easy_cleanup(curl);
		return -1;
	}

	curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &code);

	curl_easy_cleanup(curl);
	return code;
}

/*
 * Send to the CA that we want to authorise a new account.
 * This only happens once for a new account key.
 * Returns non-zero on success.
 */
static int
donewreg(struct conn *c, const struct capaths *p)
{
	int		 rc = 0;
	char		*req;
	long		 lc;

	dodbg("%s: new-reg", p->newreg);

	if ((req = json_fmt_newreg(p->agreement)) == NULL)
		warnx("json_fmt_newreg");
	else if ((lc = sreq(c, p->newreg, req)) < 0)
		warnx("%s: bad comm", p->newreg);
	else if (lc != 200 && lc != 201)
		warnx("%s: bad HTTP: %ld", p->newreg, lc);
	else if (c->buf.buf == NULL || c->buf.sz == 0)
		warnx("%s: empty response", p->newreg);
	else
		rc = 1;

	if (rc == 0 || verbose > 1)
		buf_dump(&c->buf);
	free(req);
	return rc;
}

/*
 * Request a challenge for the given domain name.
 * This must be called for each name "alt".
 * On non-zero exit, fills in "chng" with the challenge.
 */
static int
dochngreq(struct conn *c, const char *alt, struct chng *chng,
    const struct capaths *p)
{
	int		 rc = 0;
	char		*req;
	long		 lc;
	struct jsmnn	*j = NULL;

	dodbg("%s: req-auth: %s", p->newauthz, alt);

	if ((req = json_fmt_newauthz(alt)) == NULL)
		warnx("json_fmt_newauthz");
	else if ((lc = sreq(c, p->newauthz, req)) < 0)
		warnx("%s: bad comm", p->newauthz);
	else if (lc != 200 && lc != 201)
		warnx("%s: bad HTTP: %ld", p->newauthz, lc);
	else if ((j = json_parse(c->buf.buf, c->buf.sz)) == NULL)
		warnx("%s: bad JSON object", p->newauthz);
	else if (!json_parse_challenge(j, chng))
		warnx("%s: bad challenge", p->newauthz);
	else
		rc = 1;

	if (rc == 0 || verbose > 1)
		buf_dump(&c->buf);
	json_free(j);
	free(req);
	return rc;
}

/*
 * Tell the CA that a challenge response is in place.
 */
static int
dochngresp(struct conn *c, const struct chng *chng, const char *th)
{
	int	 rc = 0;
	long	 lc;
	char	*req;

	dodbg("%s: challenge", chng->uri);

	if ((req = json_fmt_challenge(chng->token, th)) == NULL)
		warnx("json_fmt_challenge");
	else if ((lc = sreq(c, chng->uri, req)) < 0)
		warnx("%s: bad comm", chng->uri);
	else if (lc != 200 && lc != 201 && lc != 202)
		warnx("%s: bad HTTP: %ld", chng->uri, lc);
	else
		rc = 1;

	if (rc == 0 || verbose > 1)
		buf_dump(&c->buf);
	free(req);
	return rc;
}

/*
 * Check with the CA whether a challenge has been processed.
 * Note: we'll only do this a limited number of times, and pause for a
 * time between checks, but this happens in the caller.
 */
static int
dochngcheck(struct conn *c, struct chng *chng)
{
	enum chngstatus	 cc;
	long		 lc;
	struct jsmnn	*j;

	dodbg("%s: status", chng->uri);

	if ((lc = nreq(c, chng->uri)) < 0) {
		warnx("%s: bad comm", chng->uri);
		return 0;
	} else if (lc != 200 && lc != 201 && lc != 202) {
		warnx("%s: bad HTTP: %ld", chng->uri, lc);
		buf_dump(&c->buf);
		return 0;
	} else if ((j = json_parse(c->buf.buf, c->buf.sz)) == NULL) {
		warnx("%s: bad JSON object", chng->uri);
		buf_dump(&c->buf);
		return 0;
	} else if ((cc = json_parse_response(j)) == -1) {
		warnx("%s: bad response", chng->uri);
		buf_dump(&c->buf);
		json_free(j);
		return 0;
	} else if (cc > 0)
		chng->status = CHNG_VALID;

	json_free(j);
	return 1;
}

static int
dorevoke(struct conn *c, const char *addr, const char *cert)
{
	char		*req;
	int		 rc = 0;
	long		 lc = 0;

	dodbg("%s: revocation", addr);

	if ((req = json_fmt_revokecert(cert)) == NULL)
		warnx("json_fmt_revokecert");
	else if ((lc = sreq(c, addr, req)) < 0)
		warnx("%s: bad comm", addr);
	else if (lc != 200 && lc != 201 && lc != 409)
		warnx("%s: bad HTTP: %ld", addr, lc);
	else
		rc = 1;

	if (lc == 409)
		warnx("%s: already revoked", addr);

	if (rc == 0 || verbose > 1)
		buf_dump(&c->buf);
	free(req);
	return rc;
}

/*
 * Submit our certificate to the CA.
 * This, upon success, will return the signed CA.
 */
static int
docert(struct conn *c, const char *addr, const char *cert)
{
	char	*req;
	int	 rc = 0;
	long	 lc;

	dodbg("%s: certificate", addr);

	if ((req = json_fmt_newcert(cert)) == NULL)
		warnx("json_fmt_newcert");
	else if ((lc = sreq(c, addr, req)) < 0)
		warnx("%s: bad comm", addr);
	else if (lc != 200 && lc != 201)
		warnx("%s: bad HTTP: %ld", addr, lc);
	else if (c->buf.sz == 0 || c->buf.buf == NULL)
		warnx("%s: empty response", addr);
	else
		rc = 1;

	if (rc == 0 || verbose > 1)
		buf_dump(&c->buf);
	free(req);
	return rc;
}

/*
 * Look up directories from the certificate authority.
 */
static int
dodirs(struct conn *c, const char *addr, struct capaths *paths)
{
	struct jsmnn	*j = NULL;
	long		 lc;
	int		 rc = 0;

	dodbg("%s: directories", addr);

	if ((lc = nreq(c, addr)) < 0)
		warnx("%s: bad comm", addr);
	else if (lc != 200 && lc != 201)
		warnx("%s: bad HTTP: %ld", addr, lc);
	else if ((j = json_parse(c->buf.buf, c->buf.sz)) == NULL)
		warnx("json_parse");
	else if (!json_parse_capaths(j, paths))
		warnx("%s: bad CA paths", addr);
	else
		rc = 1;

	if (rc == 0 || verbose > 1)
		buf_dump(&c->buf);
	json_free(j);
	return rc;
}

/*
 * Request the full chain certificate.
 */
static int
dofullchain(struct conn *c, const char *addr)
{
	int	 rc = 0;
	long	 lc;

	dodbg("%s: full chain", addr);

	if ((lc = nreq(c, addr)) < 0)
		warnx("%s: bad comm", addr);
	else if (lc != 200 && lc != 201)
		warnx("%s: bad HTTP: %ld", addr, lc);
	else
		rc = 1;

	if (rc == 0 || verbose > 1)
		buf_dump(&c->buf);
	return rc;
}

/*
 * Communicate with the ACME server.
 * We need the certificate we want to upload and our account key information.
 */
int
netproc(int kfd, int afd, int Cfd, int cfd, int dfd, int rfd,
    int newacct, int revocate, struct authority_c *authority,
    const char *const *alts, size_t altsz)
{
	int		 rc = 0;
	size_t		 i, done = 0;
	char		*cert = NULL, *thumb = NULL, *url = NULL;
	struct conn	 c;
	struct capaths	 paths;
	struct chng	*chngs = NULL;
	long		 lval;

	memset(&paths, 0, sizeof(struct capaths));
	memset(&c, 0, sizeof(struct conn));

	if (pledge("stdio inet rpath", NULL) == -1) {
		warn("pledge");
		goto out;
	}

	if (curl_global_init(CURL_GLOBAL_ALL) != 0) {
		warn("curl_global_init");
		goto out;
	}

	if (pledge("stdio inet", NULL) == -1) {
		warn("pledge");
		goto out;
	}

	/*
	 * Wait until the acctproc, keyproc, and revokeproc have started up and
	 * are ready to serve us data.
	 * Then check whether revokeproc indicates that the certificate on file
	 * (if any) can be updated.
	 */
	if ((lval = readop(afd, COMM_ACCT_STAT)) == 0) {
		rc = 1;
		goto out;
	} else if (lval != ACCT_READY) {
		warnx("unknown operation from acctproc");
		goto out;
	}

	if ((lval = readop(kfd, COMM_KEY_STAT)) == 0) {
		rc = 1;
		goto out;
	} else if (lval != KEY_READY) {
		warnx("unknown operation from keyproc");
		goto out;
	}

	if ((lval = readop(rfd, COMM_REVOKE_RESP)) == 0) {
		rc = 1;
		goto out;
	} else if (lval != REVOKE_EXP && lval != REVOKE_OK) {
		warnx("unknown operation from revokeproc");
		goto out;
	}

	/* If our certificate is up-to-date, return now. */
	if (lval == REVOKE_OK) {
		rc = 1;
		goto out;
	}

	/* Allocate main state. */
	chngs = calloc(altsz, sizeof(struct chng));
	if (chngs == NULL) {
		warn("calloc");
		goto out;
	}

	c.dfd = dfd;
	c.fd = afd;
	c.na = authority->api;

	/*
	 * Look up the API urls of the ACME server.
	 */
	if (!dodirs(&c, c.na, &paths))
		goto out;

	/*
	 * If we're meant to revoke, then wait for revokeproc to send us
	 * the certificate (if it's found at all).
	 * Following that, submit the request to the CA then notify the
	 * certproc, which will in turn notify the fileproc.
	 */
	if (revocate) {
		if ((cert = readstr(rfd, COMM_CSR)) == NULL)
			goto out;
		if (!dorevoke(&c, paths.revokecert, cert))
			goto out;
		else if (writeop(cfd, COMM_CSR_OP, CERT_REVOKE) > 0)
			rc = 1;
		goto out;
	}

	/* If new, register with the CA server. */
	if (newacct && ! donewreg(&c, &paths))
		goto out;

	/* Pre-authorise all domains with CA server. */
	for (i = 0; i < altsz; i++)
		if (!dochngreq(&c, alts[i], &chngs[i], &paths))
			goto out;

	/*
	 * We now have our challenges.
	 * We need to ask the acctproc for the thumbprint.
	 * We'll combine this to the challenge to create our response,
	 * which will be orchestrated by the chngproc.
	 */
	if (writeop(afd, COMM_ACCT, ACCT_THUMBPRINT) <= 0)
		goto out;
	else if ((thumb = readstr(afd, COMM_THUMB)) == NULL)
		goto out;

	/* We'll now ask chngproc to build the challenge. */
	for (i = 0; i < altsz; i++) {
		if (writeop(Cfd, COMM_CHNG_OP, CHNG_SYN) <= 0)
			goto out;
		else if (writestr(Cfd, COMM_THUMB, thumb) <= 0)
			goto out;
		else if (writestr(Cfd, COMM_TOK, chngs[i].token) <= 0)
			goto out;

		/* Read that the challenge has been made. */
		if (readop(Cfd, COMM_CHNG_ACK) != CHNG_ACK)
			goto out;

		/* Write to the CA that it's ready. */
		if (!dochngresp(&c, &chngs[i], thumb))
			goto out;
	}

	/*
	 * We now wait on the ACME server for each domain.
	 * Connect to the server (assume it's the same server) once
	 * every five seconds.
	 */
	for (;;) {
		for (i = 0; i < altsz; i++) {
			doddbg("%s: done %lu, altsz %lu, i %lu, status %d",
			    __func__, done, altsz, i, chngs[i].status);

			if (chngs[i].status == CHNG_VALID)
				continue;

			if (chngs[i].retry++ >= RETRY_MAX) {
				warnx("%s: too many tries", chngs[i].uri);
				goto out;
			}

			sleep(RETRY_DELAY);
			if (dochngcheck(&c, &chngs[i])) {
				if (chngs[i].status == CHNG_VALID)
					done++;
				continue;
			} else
				goto out;
		}

		if (done == altsz)
			break;
	}

	/*
	 * Write our acknowledgement that the challenges are over.
	 * The challenge process will remove all of the files.
	 */
	if (writeop(Cfd, COMM_CHNG_OP, CHNG_STOP) <= 0)
		goto out;

	/* Wait to receive the certificate itself. */
	if ((cert = readstr(kfd, COMM_CERT)) == NULL)
		goto out;

	/*
	 * Otherwise, submit the CA for signing, download the signed
	 * copy, and ship that into the certificate process for copying.
	 */
	if (!docert(&c, paths.newcert, cert))
		goto out;
	else if (writeop(cfd, COMM_CSR_OP, CERT_UPDATE) <= 0)
		goto out;
	else if (writebuf(cfd, COMM_CSR, c.buf.buf, c.buf.sz) <= 0)
		goto out;

	/*
	 * Read back the issuer from the certproc.
	 * Then contact the issuer to get the certificate chain.
	 * Write this chain directly back to the certproc.
	 */
	if ((url = readstr(cfd, COMM_ISSUER)) == NULL)
		goto out;
	else if (!dofullchain(&c, url))
		goto out;
	else if (writebuf(cfd, COMM_CHAIN, c.buf.buf, c.buf.sz) <= 0)
		goto out;

	rc = 1;
out:
	close(cfd);
	close(kfd);
	close(afd);
	close(Cfd);
	close(dfd);
	close(rfd);
	free(cert);
	free(url);
	free(thumb);
	free(c.buf.buf);
	if (chngs != NULL)
		for (i = 0; i < altsz; i++)
			json_free_challenge(&chngs[i]);
	free(chngs);
	json_free_capaths(&paths);
	return rc;
}

/* vim: set noet ts=8 sts=8 sw=8 : */
