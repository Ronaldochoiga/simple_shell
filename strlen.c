#include "shell.h"

/**
 * _strlen - return lenth of a str
 * @s: the str to measure
 *
 * Return: str len
 */
int _strlen(char *s)
{
	int j = 0;

	if (!s)
		return (0);

	while (*s++)
		j++;
	return (j);
}

/**
 * _strcmp - copies string
 * @s1: the firsize_t str
 * @s2: the second str
 *
 * Return: neg, pos or 0
 */
int _strcmp(char *s1, char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	if (*s1 == *s2)
		return (0);
	else
		return (*s1 < *s2 ? -1 : 1);
}

/**
 * sw - checks if ndle starts with hysck
 * @hysck: string to be searched
 * @ndle: substring to found
 *
 * Return: addr of next char of NULL
 */
char *sw(const char *hysck, const char *ndle)
{
	while (*ndle)
		if (*ndle++ != *hysck++)
			return (NULL);
	return ((char *)hysck);
}

/**
 * _strcat - joins 2 strs
 * @dest: destination buff
 * @src: source buff
 *
 * Return: dest buff pointer
 */
char *_strcat(char *dest, char *src)
{
	char *r = dest;

	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = *src;
	return (r);
}
