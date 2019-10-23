#ifndef COMPAT_H_fogjseogje4
#define COMPAT_H_fogjseogje4 1

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

#ifndef HAVE_reallocarray
void *reallocarray(void *ptr, size_t nmemb, size_t size);
#endif

#ifndef HAVE_recallocarray
void *recallocarray(void *ptr, size_t oldnmemb, size_t nmemb, size_t size);
#endif

#endif /* COMPAT_H_fogjseogje4 */
