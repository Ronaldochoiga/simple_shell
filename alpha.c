#include "shell.h"

/**
 * interactive - true if shell is inter mode
 * @information: struct add
 *
 * Return: 1 or 0
 */
int interactive(info_t *information)
{
	return (isatty(STDIN_FILENO) && information->readfd <= 2);
}

/**
 * is_delim - checks if charact is a delimeter
 * @c: the char to check
 * @delim: the delimeter strg
 * Return: 1 or 0
 */
int is_delim(char c, char *delim)
{
	while (*delim)
		if (*delim++ == c)
			return (1);
	return (0);
}

/**
 * _isalpha - checks for alpha charact
 * @c: The charact to input
 * Return: 1 or 0
 */

int _isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * _atoi - converts strg to an int
 * @s: the strg to convert
 * Return: 0 or converted number
 */

int _atoi(char *s)
{
	int a, sn = 1, flag = 0, output;
	unsigned int rslt = 0;

	for (a = 0; s[a] != '\0' && flag != 2; a++)
	{
		if (s[a] == '-')
			sn *= -1;

		if (s[a] >= '0' && s[a] <= '9')
		{
			flag = 1;
			rslt *= 10;
			rslt += (s[a] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sn == -1)
		output = -rslt;
	else
		output = rslt;

	return (output);
}
