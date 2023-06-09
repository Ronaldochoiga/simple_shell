#include "shell.h"

/**
 * **strtow - splits a strg into words. Repeat delimiters are ignored
 * @str: the input strg
 * @d: the delimeter strg
 * Return: a pntr to an array of strgs, or NULL on failure
 */

char **strtow(char *str, char *d)
{
	int a, b, g, m, numwords = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!d)
		d = " ";
	for (a = 0; str[a] != '\0'; a++)
		if (!is_delim(str[a], d) && (is_delim(str[a + 1], d) || !str[a + 1]))
			numwords++;

	if (numwords == 0)
		return (NULL);
	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (a = 0, b = 0; b < numwords; b++)
	{
		while (is_delim(str[a], d))
			a++;
		g = 0;
		while (!is_delim(str[a + g], d) && str[a + g])
			g++;
		s[b] = malloc((g + 1) * sizeof(char));
		if (!s[b])
		{
			for (g = 0; g < b; g++)
				free(s[g]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < g; m++)
			s[b][m] = str[a++];
		s[b][m] = 0;
	}
	s[b] = NULL;
	return (s);
}

/**
 * **strtow2 - splits a strg into words
 * @str: the input strg
 * @d: the delim
 * Return: a pntr to an array of strgs.
 */
char **strtow2(char *str, char d)
{
	int a, b, g, m, numwords = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (a = 0; str[a] != '\0'; a++)
		if ((str[a] != d && str[a + 1] == d) ||
				    (str[a] != d && !str[a + 1]) || str[a + 1] == d)
			numwords++;
	if (numwords == 0)
		return (NULL);
	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (a = 0, b = 0; b < numwords; b++)
	{
		while (str[a] == d && str[a] != d)
			a++;
		g = 0;
		while (str[a + g] != d && str[a + g] && str[a + g] != d)
			g++;
		s[b] = malloc((g + 1) * sizeof(char));
		if (!s[b])
		{
			for (g = 0; g < b; g++)
				free(s[g]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < g; m++)
			s[b][m] = str[a++];
		s[b][m] = 0;
	}
	s[b] = NULL;
	return (s);
}
