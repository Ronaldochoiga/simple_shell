#include "shell.h"

/**
 * _eputs - prts an input strg
 * @str: the strg to printed
 *
 * Return: Nothing
 */
void _eputs(char *str)
{
	int a = 0;

	if (!str)
		return;
	while (str[a] != '\0')
	{
		_eputchar(str[a]);
		a++;
	}
}

/**
 * _eputchar - writes the charact standard error
 * @c: The charact to print
 *
 * Return: i on succ
 */
int _eputchar(char c)
{
	static int a;
	static char buff[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || a >= WRITE_BUF_SIZE)
	{
		write(2, buff, a);
		a = 0;
	}
	if (c != BUF_FLUSH)
		buff[a++] = c;
	return (1);
}

/**
 * _putfd - writes the charact c to given fd
 * @c: The charact to print
 * @fd: The fd to write to
 *
 * Return: 1 on success
 */
int _putfd(char c, int fd)
{
	static int a;
	static char buff[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || a >= WRITE_BUF_SIZE)
	{
		write(fd, buff, a);
		a = 0;
	}
	if (c != BUF_FLUSH)
		buff[a++] = c;
	return (1);
}

/**
 * _putsfd - prts an input strg
 * @str: the strg to print
 * @fd: the fd to write to
 * Return: the numb of chars put
 */
int _putsfd(char *str, int fd)
{
	int a = 0;

	if (!str)
		return (0);
	while (*str)
	{
		a += _putfd(*str++, fd);
	}
	return (a);
}
