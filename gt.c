#include "shell.h"

/**
 * get_environ - return the strg array copy of our environ
 * @information: Structre with potent argmnt
 * Return: alw 0
 */
char **get_environ(info_t *information)
{
	if (!information->environ || information->env_changed)
	{
		information->environ = list_tostrs(information->env);
		information->env_changed = 0;
	}

	return (information->environ);
}

/**
 * _unsetenv - Removes an environ var
 * @information: Structure containing potent argmnt
 *  Return: 1 on delete, 0 otherwise
 * @var: the strg env var prop
 */
int _unsetenv(info_t *information, char *var)
{
	list_t *nde = information->env;
	size_t a = 0;
	char *y;

	if (!nde || !var)
		return (0);

	while (nde)
	{
		y = starts_with(nde->str, var);
		if (y && *y == '=')
		{
			information->env_changed = delete_nde_at_ind(&(information->env), a);
			a = 0;
			nde = information->env;
			continue;
		}
		nde = nde->next;
		a++;
	}
	return (information->env_changed);
}

/**
 * _setenv - inits a new environ
 * @information: Structure containing potent argmnt.
 * @var: the strg env var property
 * @value: the strg env var value
 *  Return: alw 0
 */
int _setenv(info_t *information, char *var, char *value)
{
	char *buff = NULL;
	list_t *nde;
	char *y;

	if (!var || !value)
		return (0);

	buff = malloc(_strlen(var) + _strlen(value) + 2);
	if (!buff)
		return (1);
	_strcpy(buff, var);
	_strcat(buff, "=");
	_strcat(buff, value);
	nde = information->env;
	while (nde)
	{
		y = starts_with(nde->str, var);
		if (y && *y == '=')
		{
			free(nde->str);
			nde->str = buff;
			information->env_changed = 1;
			return (0);
		}
		nde = nde->next;
	}
	add_nde_end(&(information->env), buff, 0);
	free(buff);
	information->env_changed = 1;
	return (0);
}
