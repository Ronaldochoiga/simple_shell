#include "shell.h"

/**
 * interactive - gives val after interaction
 * @inf: structural address
 *
 * Return: 1 or zero
 */
int interactive(inf_t *inf)
{
	return (isatty(STDIN_FILEN0) && inf->rfd <= 2);
}

/**
 * is_delim - tells if the funct is a delim
 * @c: the char to checked by the mf
 * @delim: the delim str
 * Return: 1 or zero
 */
int is_delim(char c, char *delim)
{
	while (*delim)
		if (*delim++ == c)
			return (1);
	return (0);
}

/**
 * _ipa - check alphabetic chars
 * @c: input char
 * Return: 1 or zero
 */

int _ipa(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * _stoi - changes str to int
 * @s: the string to convert
 * Return: 0 or converted str
 */

int _stoi(char *s)
{
	int i, sn = 1, fg = 0, opt;
	unsigned int result = 0;

	for (i = 0; s[i] != '\0' && fg != 2; i++)
	{
		if (s[i] == '-')
			sn *= -1;
		if (s[i] >= '0' && s[i] <= '9')
		{
			fg = 1;
			result *= 10;
			result += (s[i] - '0');
		}
		else if (fg == 1)
			fg = 2;
	}
	if (sn == -1)
		opt = -result;
	else
		opt = result;

	return (opt);
}
