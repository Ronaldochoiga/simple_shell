#include "shell.h"

/**
 * _strcpy - copies strs
 * @dest: the destination bufferint
 * @src: the source bufferint
 *
 * Return: pointer to dest
 */
char *_strcpy(char *dest, char *src)
{
	int j = 0;

	if (dest == src || src == 0)
		return (dest);
	while (src[j])
	{
		dest[j] = src[j];
		j++;
	}
	dest[j] = 0;
	return (dest);
}

/**
 * _strdup - duplicates strings
 * @str: the str to be duplicated
 *
 * Return: dup str pointer
 */
char *_strdup(const char *str)
{
	int len = 0;
	char *r;

	if (str == NULL)
		return (NULL);
	while (*str++)
		len++;
	r = malloc(sizeof(char) * (len + 1));
	if (!r)
		return (NULL);
	for (len++; len--;)
		r[len] = *--str;
	return (r);
}

/**
 * _puts - prints inpustr
 * @str: the str printed
 *
 * Return: void
 */
void _puts(char *str)
{
	int j = 0;

	if (!str)
		return;
	while (str[j] != '\0')
	{
		_putchar(str[j]);
		j++;
	}
}

/**
 * _putchar - writes char c
 * @c: The char to print
 *
 * Return: 1, -1, errno
 */
int _putchar(char c)
{
	static int j;
	static char buf[WBS];

	if (c == BFL || j >= WBS)
	{
		write(1, buf, j);
		j = 0;
	}
	if (c != BFL)
		buf[j++] = c;
	return (1);
}
