#include "shell.h"

/**
 * ichain - check if current is delimeter
 * @inf: the param struct
 * @buf: the char buff
 * @p: addr of current pos
 *
 * Return: 1 or 0
 */
int ichain(inf_t *inf, char *buf, size_t *p)
{
	size_t i = *p;

	if (buf[i] == '|' && buf[i + 1] == '|')
	{
		buf[i] = 0;
		i++;
		inf->cbt = CMDO;
	}
	else if (buf[i] == '&' && buf[i + 1] == '&')
	{
		buf[i] = 0;
		i++;
		inf->cbt = CMD_AND;
	}
	else if (buf[i] == ';')
	{
		buf[i] = 0;
		inf->cbt = CMD_CHAIN;
	}
	else
		return (0);
	*p = i;
	return (1);
}

/**
 * chchain - checks whether chaining should continue
 * @inf: the functional parameter
 * @buf: the char buff
 * @p: addr of current pos
 * @i: start pos
 * @len: len of bufferint
 *
 * Return: Void
 */
void chchain(inf_t *inf, char *buf, size_t *p, size_t i, size_t len)
{
	size_t a = *p;

	if (inf->cbt == CMD_AND)
	{
		if (inf->sts)
		{
			buf[i] = 0;
			a = len;
		}
	}
	if (inf->cbt == CMDO)
	{
		if (!inf->sts)
		{
			buf[i] = 0;
			a = len;
		}
	}

	*p = a;
}

/**
 * repalias - replaces tekenized str
 * @inf: the param struct
 *
 * Return: 1 or 0
 */
int repalias(inf_t *inf)
{
	int j;
	lt *nde;
	char *p;

	for (j = 0; j < 10; j++)
	{
		nde = st_nde(inf->alias, inf->argv[0], '=');
		if (!nde)
			return (0);
		free(inf->argv[0]);
		p = _strchr(nde->str, '=');
		if (!p)
			return (0);
		p = _strdup(p + 1);
		if (!p)
			return (0);
		inf->argv[0] = p;
	}
	return (1);
}
/**
 * repvrs - replace vriables
 *
 * @inf: structural parameter
 *
 * Return: 1 or zero
 */
int repvrs(inf_t *inf)
{
	int j = 0;
	lt *nde;

	for (j = 0; inf->argv[j]; j++)
	{
		if (inf->argv[j][0] != '$' || !inf->argv[j][1])
			continue;

		if (!_strcmp(inf->argv[j], "$?"))
		{
			r_str(&(inf->argv[j]),
			      _strdup(convertnum(inf->sts, 10, 0)));
			continue;
		}
		if (!_strcmp(inf->argv[j], "$$"))
		{
			r_str(&(inf->argv[j]),
			      _strdup(convertnum(getpid(), 10, 0)));
			continue;
		}
		nde = st_nde(inf->env, &inf->argv[j][1], '=');
		if (nde)
		{
			r_str(&(inf->argv[j]),
			      _strdup(_strchr(nde->str, '=') + 1));
			continue;
		}
		r_str(&inf->argv[j], _strdup(""));

	}
	return (0);
}

/**
 * r_str - replaces str
 * @old: addr of str
 * @new: new str
 *
 * Return: 1 or 0
 */
int r_str(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}
