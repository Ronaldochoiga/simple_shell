#include "shell.h"

/**
 * _myhist - displays the hisize_t list,
 * @inf: Struct has potent args
 *  Return: Always zero
 */
int _myhist(inf_t *inf)
{
	print_lst(inf->hist);
	return (0);
}

/**
 * unsetal - set string alias
 * @inf: parameter functional
 * @str: the stg alias
 *
 * Return: Always 0or 1
 */
int unsetal(inf_t *inf, char *str)
{
	char *i, j;
	int r;

	i = _strchr(str, '=');
	if (!i)
		return (1);
	j = *i;
	*i = 0;
	r = del_ind(&(inf->alias),
		    get_ind(inf->alias, st_nde(inf->alias, str, -1)));
	*i = j;
	return (r);
}

/**
 * setal - sets al to str
 * @inf: parameter structure
 * @str: the str alias
 *
 * Return: Always zero or 1
 */
int setal(inf_t *inf, char *str)
{
	char *p;

	p = _strchr(str, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (unsetal(inf, str));
	unsetal(inf, str);
	return (add_end(&(inf->alias), str, 0) == NULL);
}

/**
 * printal - print als to thg str
 * @nde: the alias nde
 *
 * Return: Always zero or 1
 */
int printal(lt *nde)
{
	char *p = NULL, *i = NULL;

	if (nde)
	{
		p = _strchr(nde->str, '=');
		for (i = nde->str; i <= p; i++)
			_putchar(*i);
		_putchar('\'');
		_puts(p + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * _myal - mimic the alias blin
 * @inf: fp with potent args
 *  Return: Always zero
 */
int _myal(inf_t *inf)
{
	int j = 0;
	char *p = NULL;
	lt *nde = NULL;

	if (inf->argc == 1)
	{
		nde = inf->alias;
		while (nde)
		{
			printal(nde);
			nde = nde->next;
		}
		return (0);
	}
	for (j = 1; inf->argv[j]; j++)
	{
		p = _strchr(inf->argv[j], '=');
		if (p)
			setal(inf, inf->argv[j]);
		else
			printal(st_nde(inf->alias, inf->argv[j], '='));
	}
	return (0);
}
