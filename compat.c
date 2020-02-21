#include "compat.h"

#include <errno.h>
#include <stdint.h>
#include <string.h>

#ifndef HAVE_reallocarray
void *reallocarray(void *ptr, size_t nmemb, size_t size)
{
	/* Close enough */
	return recallocarray(ptr, 0, nmemb, size);
}
#endif

#ifndef HAVE_recallocarray
// From openbsd
//     commit: 3f0eb563136eb507c769562c93646288721f7ea4
//     file  : lib/libc/stdlib/recallocarray.c
//
// Slightly modified.

/*
 * This is sqrt(SIZE_MAX+1), as s1*s2 <= SIZE_MAX
 * if both s1 < MUL_NO_OVERFLOW and s2 < MUL_NO_OVERFLOW
 */
#define MUL_NO_OVERFLOW ((size_t)1 << (sizeof(size_t) * 4))

void *
recallocarray(void *ptr, size_t oldnmemb, size_t newnmemb, size_t size)
{
	size_t oldsize, newsize;
	void *newptr;

	if (ptr == NULL)
		return calloc(newnmemb, size);

	if ((newnmemb >= MUL_NO_OVERFLOW || size >= MUL_NO_OVERFLOW) &&
	    newnmemb > 0 && SIZE_MAX / newnmemb < size) {
		errno = ENOMEM;
		return NULL;
	}
	newsize = newnmemb * size;

	if ((oldnmemb >= MUL_NO_OVERFLOW || size >= MUL_NO_OVERFLOW) &&
	    oldnmemb > 0 && SIZE_MAX / oldnmemb < size) {
		errno = EINVAL;
		return NULL;
	}
	oldsize = oldnmemb * size;

	newptr = malloc(newsize);
	if (newptr == NULL)
		return NULL;

	if (newsize > oldsize) {
		memcpy(newptr, ptr, oldsize);
		memset((char *)newptr + oldsize, 0, newsize - oldsize);
	} else
		memcpy(newptr, ptr, newsize);

	memset(ptr, 0, oldsize);
	free(ptr);

	return newptr;
}
#endif
