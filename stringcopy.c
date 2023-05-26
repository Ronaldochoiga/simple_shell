#include "shell.h"

/**
 **_strncpy - copies a strg
 *@dest: the dest strg to be copied to
 *@src: the source strg
 *@n: the amount of characts to be copied
 *Return: the conctd strg
 */
char *_strncpy(char *dest, char *src, int n)
{
	int a, b;
	char *s = dest;

	a = 0;
	while (src[a] != '\0' && a < n - 1)
	{
		dest[a] = src[a];
		a++;
	}
	if (a < n)
	{
		b = a;
		while (b < n)
		{
			dest[b] = '\0';
			b++;
		}
	}
	return (s);
}

/**
 **_strncat - concts two strgs
 *@dest: the frst strg
 *@src: the second strg
 *@n: the amount of bytes to be maximally used
 *Return: the conctd strg
 */
char *_strncat(char *dest, char *src, int n)
{
	int a, b;
	char *s = dest;

	a = 0;
	b = 0;
	while (dest[a] != '\0')
		a++;
	while (src[b] != '\0' && b < n)
	{
		dest[a] = src[b];
		a++;
		b++;
	}
	if (b < n)
		dest[a] = '\0';
	return (s);
}

/**
 **_strchr - locts a charact in a strg
 *@s: the strg to be parsed
 *@c: the charact to look for
 *Return: a pntr to the memory area s
 */
char *_strchr(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}
