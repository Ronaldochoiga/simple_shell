#include "shell.h"

/**
 * _myv - prints the curr environ
 * @inf: Struct has potent args
 * Return: Always zero
 */
int _myv(inf_t *inf)
{
	plstr(inf->env);
	return (0);
}

/**
 * gev - get val of environment vriables
 * @inf: Struct with potent args
 * @name: env vrname
 *
 * Return: the environ val
 */
char *gev(inf_t *inf, const char *name)
{
	lt *nde = inf->env;
	char *q;

	while (nde)
	{
		q = sw(nde->str, name);
		if (q && *q)
			return (q);
		nde = nde->next;
	}
	return (NULL);
}

/**
 * _mysev - Initialize a new environ
 * @inf: Struct with potent args
 *  Return: Always 0
 */
int _mysev(inf_t *inf)
{
	if (inf->argc != 3)
	{
		_eps("Incorrect num of args\n");
		return (1);
	}
	if (_sev(inf, inf->argv[1], inf->argv[2]))
		return (0);
	return (1);
}

/**
 * _myunsev - Rm args
 * @inf: Struct with potent args
 * Return: Always zero
 */
int _myunsev(inf_t *inf)
{
	int i;

	if (inf->argc == 1)
	{
		_eps("few args\n");
		return (1);
	}
	for (i = 1; i <= inf->argc; i++)
		_unsev(inf, inf->argv[i]);
	return (0);
}

/**
 * popenvl - pops env linked lists
 * @inf: struct with potent args
 * Return: Always zero
 */
int popenvl(inf_t *inf)
{
	lt *nde = NULL;
	size_t j;

	for (j = 0; environ[j]; ++)
		add_end(&nde, environ[j], 0);
	inf->env = nde;
	return (0);
}
