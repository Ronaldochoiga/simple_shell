#include "shell.h"

/**
 * _errstoi - convert str to int
 * @s: the string to convert
 * Return: 0, converted no ot -1
 */
int _errstoi(char *s)
{
	int j = 0;
	unsigned long int result = 0;

	if (*s == '+')
		s++;
	for (j = 0;  s[j] != '\0'; j++)
	{
		if (s[j] >= '0' && s[j] <= '9')
		{
			result *= 10;
			result += (s[j] - '0');
			if (result > IMAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (result);
}

/**
 * printer - print err msg
 * @inf: parameter with potential args
 * @estr: error str
 * Return: 0, converted num or -1
 */
void printer(inf_t *inf, char *estr)
{
	_eps(inf->fname);
	_eps(": ");
	print_d(inf->linco, STDERR_FILENO);
	_eps(": ");
	_eps(inf->argv[0]);
	_eps(": ");
	_eps(estr);
}

/**
 * print_d - print decimal no to base 10
 * @input: the inp
 * @fd: the filedescriptor
 *
 * Return: num of printed chars
 */
int print_d(int input, int fd)
{
	int (*__putchar)(char) = _putchar;
	int j, c = 0;
	unsigned int _abs_, curr;

	if (fd == STDERR_FILENO)
		__putchar = _epc;
	if (input < 0)
	{
		_abs_ = -input;
		__putchar('-');
		c++;
	}
	else
		_abs_ = input;
	curr = _abs_;
	for (j = 1000000000; j > 1; j /= 10)
	{
		if (_abs_ / j)
		{
			__putchar('0' + curr / j);
			c++;
		}
		curr %= j;
	}
	__putchar('0' + curr);
	c++;
	return (c);
}

/**
 * convertnum - converts funct
 * @num: num to be converted
 * @bse: bse
 * @fgs: args fgs
 *
 * Return: string
 */
char *convertnum(long int num, int bse, int fgs)
{
	static char *arr;
	static char bufferint[50];
	char sn = 0;
	char *qtr;
	unsigned long n = num;

	if (!(fgs & CONVERT_UNSIGNED) && num < 0)
	{
		n = -num;
		sn = '-';
	}
	arr = fgs & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	qtr = &bufferint[49];
	*qtr = '\0';
	do      {
		*--qtr = arr[n % bse];
		n /= bse;
	} while (n != 0);

	if (sn)
		*--qtr = sn;
	return (qtr);
}

/**
 * rmcomments - function replace firsize_t occurence of '#' with '\0'
 * @buf: add of the modifying str
 *
 * Return: Always zero;
 */
void rmcomments(char *buf)
{
	int j;

	for (j = 0; buf[j] != '\0'; j++)
		if (buf[j] == '#' && (!j || buf[j - 1] == ' '))
		{
			buf[j] = '\0';
			break;
		}
}