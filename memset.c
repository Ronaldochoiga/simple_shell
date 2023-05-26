#include "shell.h"

/**
 * _memset - fill mem with const byte
 * @s: memory area pointer
 * @b: bytes to fill s
 * @n: amount to filol
 * Return: s
 */
char *_memset(char *s, char b, unsigned int n)
{
	unsigned int j;

	for (j = 0; j < n; j++)
		s[j] = b;
	return (s);
}

/**
 * ffr - free str from str
 * @pp: str of str
 */
void ffr(char **pp)
{
	char **x = pp;

	if (!pp)
		return;
	while (*pp)
		free(*pp++);
	free(x);
}

/**
 * _realloc - reallocates mem block
 * @qtr: prev block pointer
 * @oldsze: prev block byte size
 * @newsze: new block byte size
 *
 * Return: old block pointer
 */
void *_realloc(void *qtr, unsigned int oldsze, unsigned int newsze)
{
	char *p;

	if (!qtr)
		return (malloc(newsze));
	if (!newsze)
		return (free(qtr), NULL);
	if (newsze == oldsze)
		return (qtr);

	p = malloc(newsze);
	if (!p)
		return (NULL);

	oldsze = oldsze < newsze ? oldsze : newsze;
	while (oldsze--)
		p[oldsze] = ((char *)qtr)[oldsze];
	free(qtr);
	return (p);
}

