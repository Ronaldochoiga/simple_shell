#include "shell.h"

/**
 * _erratoi - converts strg to an int
 * @s: the strg to convert
 * Return: 0 or 1 or rslt
 */
int _erratoi(char *s)
{
	int a = 0;
	unsigned long int rslt = 0;

	if (*s == '+')
		s++;
	for (a = 0;  s[a] != '\0'; a++)
	{
		if (s[a] >= '0' && s[a] <= '9')
		{
			rslt *= 10;
			rslt += (s[a] - '0');
			if (rslt > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (rslt);
}

/**
 * print_error - prts an err msg
 * @information: the param & return information struct
 * @estr: strg with specific error type
 * Return: 0 or -1
 */
void print_error(info_t *information, char *estr)
{
	_eputs(information->fname);
	_eputs(": ");
	print_d(information->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(information->argv[0]);
	_eputs(": ");
	_eputs(estr);
}

/**
 * print_d - fnct prts a decimal (int) numb (base 10)
 * @input: the input
 * @fd: the fd to write to
 *
 * Return: numb of characts printed
 */
int print_d(int input, int fd)
{
	int (*__putchar)(char) = _putchar;
	int a, count = 0;
	unsigned int _abs_, curr;

	if (fd == STDERR_FILENO)
		__putchar = _eputchar;
	if (input < 0)
	{
		_abs_ = -input;
		__putchar('-');
		count++;
	}
	else
		_abs_ = input;
	curr = _abs_;
	for (a = 1000000000; a > 1; a /= 10)
	{
		if (_abs_ / a)
		{
			__putchar('0' + curr / a);
			count++;
		}
		curr %= a;
	}
	__putchar('0' + curr);
	count++;

	return (count);
}

/**
 * convert_number - converter fnct
 * @num: numb
 * @base: base
 * @flags: argmnt flags
 *
 * Return: strg
 */
char *convert_number(long int num, int base, int flags)
{
	static char *array;
	static char bf[50];
	char sn = 0;
	char *ptr;
	unsigned long n = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		n = -num;
		sn = '-';

	}
	array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &bf[49];
	*ptr = '\0';

	do	{
		*--ptr = array[n % base];
		n /= base;
	} while (n != 0);

	if (sn)
		*--ptr = sn;
	return (ptr);
}

/**
 * remove_comments - fnct replaces
 * @buff: add of the strg to modify
 *
 * Return: alw 0;
 */
void remove_comments(char *buff)
{
	int a;

	for (a = 0; buff[a] != '\0'; a++)
		if (buff[a] == '#' && (!a || buff[a - 1] == ' '))
		{
			buff[a] = '\0';
			break;
		}
}
