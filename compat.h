#ifndef COMPAT_H_fogjseogje4
#define COMPAT_H_fogjseogje4 1

#include <sys/types.h>
#include <stdarg.h>

#include "config.h"

/* HACK: OpenSSL symbols pollute parser */
#ifndef ACMECLIENT_PARSER
#include <openssl/rsa.h>

#if OPENSSL_VERSION_NUMBER < 0x10100000L || defined(LIBRESSL_VERSION_NUMBER)
# define COMPAT_OPENSSL_get_n(r) (r->n)
# define COMPAT_OPENSSL_get_e(r) (r->e)
# define COMPAT_OPENSSL_pkey_type(pkey) (EVP_PKEY_type(pkey->type))
# define EVP_MD_CTX_new EVP_MD_CTX_create
# define EVP_MD_CTX_free EVP_MD_CTX_destroy
#else
# define COMPAT_OPENSSL_get_n(r) (RSA_get0_n(r))
# define COMPAT_OPENSSL_get_e(r) (RSA_get0_e(r))
# define COMPAT_OPENSSL_pkey_type(pkey) (EVP_PKEY_base_id(pkey))
#endif
#endif

#ifndef HAVE_reallocarray
void *reallocarray(void *ptr, size_t nmemb, size_t size);
#endif

#ifndef HAVE_recallocarray
void *recallocarray(void *ptr, size_t oldnmemb, size_t nmemb, size_t size);
#endif

#ifndef HAVE_err
void err(int, const char*, ...);
void warn(const char*, ...);
void errx(int, const char*, ...);
void warnx(const char*, ...);
void vwarnx(const char*, va_list);
#else
# include <err.h>
#endif

#ifndef HAVE_asprintf
int asprintf(char **, const char *, ...);
#endif

#ifndef HAVE_vasprintf
int vasprintf(char **, const char *, va_list);
#endif

#ifndef HAVE_strlcat
size_t strlcat(char *, const char *, size_t);
#endif

#ifndef HAVE_strtonum
long long strtonum(const char *, long long, long long, const char **);
#endif

/*
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 *	@(#)queue.h	8.5 (Berkeley) 8/20/94
 */
#ifndef LIST_FIRST
#define	LIST_FIRST(head)		((head)->lh_first)
#endif
#ifndef LIST_END
#define	LIST_END(head)			NULL
#endif
#ifndef LIST_NEXT
#define	LIST_NEXT(elm, field)		((elm)->field.le_next)
#endif
#ifndef LIST_FOREACH
#define LIST_FOREACH(var, head, field)					\
	for((var) = LIST_FIRST(head);					\
	    (var)!= LIST_END(head);					\
	    (var) = LIST_NEXT(var, field))
#endif
#ifndef TAILQ_HEAD_INITIALIZER
#define TAILQ_HEAD_INITIALIZER(head)					\
	{ NULL, &(head).tqh_first }
#endif
#ifndef TAILQ_FIRST
#define	TAILQ_FIRST(head)		((head)->tqh_first)
#endif
#ifndef TAILQ_END
#define	TAILQ_END(head)			NULL
#endif
#ifndef TAILQ_NEXT
#define	TAILQ_NEXT(elm, field)		((elm)->field.tqe_next)
#endif
#ifndef TAILQ_PREV
#define TAILQ_PREV(elm, headname, field)				\
	(*(((struct headname *)((elm)->field.tqe_prev))->tqh_last))
#endif
#ifndef TAILQ_EMPTY
#define	TAILQ_EMPTY(head)						\
	(TAILQ_FIRST(head) == TAILQ_END(head))
#endif
#ifndef TAILQ_FOREACH
#define TAILQ_FOREACH(var, head, field)					\
	for((var) = TAILQ_FIRST(head);					\
	    (var) != TAILQ_END(head);					\
	    (var) = TAILQ_NEXT(var, field))
#endif
#ifndef TAILQ_FOREACH_SAFE
#define	TAILQ_FOREACH_SAFE(var, head, field, tvar)			\
	for ((var) = TAILQ_FIRST(head);					\
	    (var) != TAILQ_END(head) &&					\
	    ((tvar) = TAILQ_NEXT(var, field), 1);			\
	    (var) = (tvar))
#endif

#endif /* COMPAT_H_fogjseogje4 */
