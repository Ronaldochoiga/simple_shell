#include "shell.h"

/**
 * get_environ - return str arr copy
 * @inf: Struc with potential args
 * Return: Always zero
 */
char **get_environ(inf_t *inf)
{
	if (!inf->environ || inf->changed_env)
	{
		inf->environ = lst(inf->env);
		inf->changed_env = 0;
	}

	return (inf->environ);
}

/**
 * _unsev - Remove an environm vr
 * @inf: Struct with potent args
 * @vr: the str env vr
 *Return: 1 or zero
 */
int _unsev(inf_t *inf, char *vr)
{
	lt *nde = inf->env;
	size_t j = 0;
	char *q;

	if (!nde || !vr)
		return (0);
	while (nde)
	{
		q = sw(nde->str, vr);
		if (q && *q == '=')
		{
			inf->changed_env = del_ind(&(inf->env), j);
			j = 0;
			nde = inf->env;
			continue;
		}
		nde = nde->next;
		j++;
	}
	return (inf->changed_env);
}

/**
 * _sev - stes a new environment
 * @inf: Struct with potential args
 * @vr: the str env vr prop
 * @val: the str val
 *  Return: Always zero
 */
int _sev(inf_t *inf, char *vr, char *val)
{
	char *buf = NULL;
	lt *nde;
	char *q;

	if (!vr || !val)
		return (0);

	buf = malloc(_strlen(vr) + _strlen(val) + 2);
	if (!buf)
		return (1);
	_strcpy(buf, vr);
	_strcat(buf, "=");
	_strcat(buf, val);
	nde = inf->env;
	while (nde)
	{
		q = sw(nde->str, vr);
		if (q && *q == '=')
		{
			free(nde->str);
			nde->str = buf;
			inf->changed_env = 1;
			return (0);
		}
		nde = nde->next;
	}
	add_end(&(inf->env), buf, 0);
	free(buf);
	inf->changed_env = 1;
	return (0);
}
