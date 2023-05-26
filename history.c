#include "shell.h"

/**
 * _ourhistory - displays hist of lst
 * @information: Structure has potent argmnt
 *  Return: alw 0
 */
int _ourhistory(info_t *information)
{
	print_list(information->history);
	return (0);
}

/**
 * unset_alias - sets alias to strg
 * @information: param struct
 * @str: the strg alias
 *
 * Return: alw 0 on success, 1 on error
 */
int unset_alias(info_t *information, char *str)
{
	char *y, c;
	int ret;

	y = _strchr(str, '=');
	if (!y)
		return (1);
	c = *y;
	*y = 0;
	ret = delete_nde_at_ind(&(information->alias),
		get_nde_ind(information->alias, nde_starts_with(information->alias, str, -1)));
	*y = c;
	return (ret);
}

/**
 * set_alias - sets alias to strg
 * @information: param struct
 * @str: the strg alias
 *
 * Return: alw 0 on success, 1 on error
 */
int set_alias(info_t *information, char *str)
{
	char *y;

	y = _strchr(str, '=');
	if (!y)
		return (1);
	if (!*++y)
		return (unset_alias(information, str));

	unset_alias(information, str);
	return (add_nde_end(&(information->alias), str, 0) == NULL);
}

/**
 * print_alias - prts an alias strg
 * @nde: the alias nde
 *
 * Return: 0 or 1
 */
int print_alias(list_t *nde)
{
	char *y = NULL, *a = NULL;

	if (nde)
	{
		y = _strchr(nde->str, '=');
		for (a = nde->str; a <= y; a++)
		_putchar(*a);
		_putchar('\'');
		_puts(y + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * _ouralias - imitates the alias bltin (man alias)
 * @information: Structure has potent argmnt
 *  Return: alw zero
 */
int _ouralias(info_t *information)
{
	int a = 0;
	char *y = NULL;
	list_t *nde = NULL;

	if (information->argc == 1)
	{
		nde = information->alias;
		while (nde)
		{
			print_alias(nde);
			nde = nde->next;
		}
		return (0);
	}
	for (a = 1; information->argv[a]; a++)
	{
		y = _strchr(information->argv[a], '=');
		if (y)
			set_alias(information, information->argv[a]);
		else
			print_alias(nde_starts_with(information->alias, information->argv[a], '='));
	}

	return (0);
}
