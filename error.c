#include "shell.h"

/**
 * _eps - print an input str
 * @str: the str to print
 *
 * Return: void
 */
void _eps(char *str)
{
	int i = 0;

	if (!str)
		return;
	while (str[i] != '\0')
	{
		_epc(str[i]);
		i++;
	}
}

/**
 * _epc - writes the char in std error
 * @c: The char to be printedprint
 *
 * Return: 1 or -1
 */
int _epc(char c)
{
	static int j;
	static char buf[WBS];

	if (c == BFL || j >= WBS)
	{
		write(2, buf, j);
		j = 0;
	}
	if (c != BFL)
		buf[j++] = c;
	return (1);
}

/**
 * _ptfd - write c to given fd
 * @c: The char to print
 * @fd: The filedescriptor
 *
 * Return: 1, -1 or errno
 */
int _ptfd(char c, int fd)
{
	static int j;
	static char buf[WBS];

	if (c == BFL || j >= WBS)
	{
		write(fd, buf, j);
		j = 0;
	}
	if (c != BFL)
		buf[j++] = c;
	return (1);
}

/**
 * _psfd - print input dtr
 * @str: the str to print
 * @fd: the filedescriptor
 *
 * Return: chars put
 */
int _psfd(char *str, int fd)
{
	int j = 0;

	if (!str)
		return (0);
	while (*str)
	{
		j += _ptfd(*str++, fd);
	}
	return (j);
}
