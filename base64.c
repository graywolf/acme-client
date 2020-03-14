/*	$Id: base64.c,v 1.9 2017/01/24 13:32:55 jsing Exp $ */
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

#include <stdlib.h>
#include <string.h>

#include <openssl/bio.h>
#include <openssl/evp.h>
#include <openssl/buffer.h>

#include "config.h"
#include "compat.h"
#include "extern.h"

static int
x_b64_ntop(const unsigned char *src, int src_len, char *dst, int dst_len);

/*
 * Compute the maximum buffer required for a base64 encoded string of
 * length "len".
 */
size_t
base64len(size_t len)
{

	return (len + 2) / 3 * 4 + 1;
}

/*
 * Pass a stream of bytes to be base64 encoded, then converted into
 * base64url format.
 * Returns NULL on allocation failure (not logged).
 */
char *
base64buf_url(const char *data, size_t len)
{
	size_t	 i, sz;
	char	*buf;

	sz = base64len(len);
	if ((buf = malloc(sz)) == NULL)
		return NULL;

	x_b64_ntop((const unsigned  char *)data, len, buf, sz);

	for (i = 0; i < sz; i++)
		switch (buf[i]) {
		case '+':
			buf[i] = '-';
			break;
		case '/':
			buf[i] = '_';
			break;
		case '=':
			buf[i] = '\0';
			break;
		}

	return buf;
}

static int
x_b64_ntop(const unsigned char *src, int src_len, char *dst, int dst_len)
{
	int len = 0;
	int total_len = 0;

	BIO *buf;
	BUF_MEM *ptr;

	buf = BIO_new(BIO_s_mem());
	buf = BIO_push(BIO_new(BIO_f_base64()), buf);

	BIO_set_flags(buf, BIO_FLAGS_BASE64_NO_NL);
	(void)BIO_set_close(buf, BIO_CLOSE);

	do {
		len = BIO_write(buf, src + total_len, src_len - total_len);
		if (len > 0) {
			total_len += len;
		}
	} while (len && BIO_should_retry(buf));

	if (BIO_flush(buf) != 1) {
		warnx("BIO_flush OOM");
		/* Since we are working with memory buffers, only reason to fail
		 * is OOM. And due to API of this function there is not a way
		 * to report it up. So just die. */
		exit(1);
	}

	BIO_get_mem_ptr(buf, &ptr);
	len = ptr->length;

	memcpy(dst, ptr->data, dst_len < len ? dst_len : len);
	dst[dst_len < len ? dst_len : len] = '\0';

	BIO_free_all(buf);

	if (dst_len < len) {
		return -1;
	}

	return len;
}
