#ifndef LIBC_H
#define LIBC_H

#include "types.h"

void *memset(void *s, int c, int n);
void *memcpy(void *dest, const void *src, int n);
int memcmp(const void *s1, const void *s2, int n);
int strlen(const char *str);
void exit(int status);

static inline int isalpha(int c)
{
	return ((unsigned)c | 32) - 'a' < 26;
}

static inline int isdigit(int c)
{
	return (unsigned)c - '0' < 10;
}

static inline int isalnum(int c)
{
	return isalpha(c) || isdigit(c);
}

#endif
