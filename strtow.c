#include "shell.h"

/**
 * **strtow - two word split
 * @str: the input str
 * @d: the delim str
 * Return: pointer to array of strs
 */

char **strtow(char *str, char *d)
{
	int a, b, c, e, nwrds = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!d)
		d = " ";
	for (a = 0; str[a] != '\0'; a++)
		if (!is_delim(str[a], d) && (is_delim(str[a + 1], d) || !str[a + 1]))
			nwrds++;

	if (nwrds == 0)
		return (NULL);
	s = malloc((1 + nwrds) * sizeof(char *));
	if (!s)
		return (NULL);
	for (b = 0, b = 0; b < nwrds; b++)
	{
		while (is_delim(str[a], d))
			a++;
		c = 0;
		while (!is_delim(str[a + c], d) && str[a + c])
			c++;
		s[b] = malloc((c + 1) * sizeof(char));
		if (!s[b])
		{
			for (c = 0; c < b; c++)
				free(s[c]);
			free(s);
			return (NULL);
		}
		for (e = 0; e < c; e++)
			s[b][e] = str[a++];
		s[b][e] = 0;
	}
	s[b] = NULL;
	return (s);
}

/**
 * **strtow2 - two word splitting
 * @str: the input str
 * @d: the delim
 * Return: sdtring array pointer
 */
char **strtow2(char *str, char d)
{
	int a, b, c, e, nwrds = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (a = 0; str[a] != '\0'; a++)
		if ((str[a] != d && str[a + 1] == d) ||
		    (str[a] != d && !str[a + 1]) || str[a + 1] == d)
			nwrds++;
	if (nwrds == 0)
		return (NULL);
	s = malloc((1 + nwrds) * sizeof(char *));
	if (!s)
		return (NULL);
	for (a = 0, b = 0; b < nwrds; b++)
	{
		while (str[a] == d && str[a] != d)
			a++;
		c = 0;
		while (str[a + c] != d && str[a + c] && str[a + c] != d)
			c++;
		s[b] = malloc((c + 1) * sizeof(char));
		if (!s[b])
		{
			for (c = 0; c < b; c++)
				free(s[c]);
			free(s);
			return (NULL);
		}
		for (e = 0; e < c; e++)
			s[b][e] = str[a++];
		s[b][e] = 0;
	}
	s[b] = NULL;
	return (s);
}
