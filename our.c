#include "shell.h"

/**
 * _ourenv - prts the curr environ
 * @information: Structure has potent argmnt
 * Return: alw 0
 */
int _ourenv(info_t *information)
{
	print_list_str(information->env);
	return (0);
}

/**
 * _gtenv - gets the value of an environ variable
 * @information: Structure has potent args
 * @name: env var name
 *
 * Return: the value
 */
char *_gtenv(info_t *information, const char *name)
{
	list_t *nde = information->env;
	char *y;

	while (nde)
	{
		y = starts_with(nde->str, name);
		if (y && *y)
			return (y);
		nde = nde->next;
	}
	return (NULL);
}

/**
 * _oursetenv - inits a new environ var
 * @information: Structure has potent argmnt
 *  Return: alw 0
 */
int _oursetenv(info_t *information)
{
	if (information->argc != 3)
	{
		_eputs("Incorrect numb of arguements\n");
		return (1);
	}
	if (_setenv(information, information->argv[1], information->argv[2]))
		return (0);
	return (1);
}

/**
 * _ourunsetenv - Removed environ var
 * @information: Structure has potent args
 * Return: alw 0
 */
int _ourunsetenv(info_t *information)
{
	int a;

	if (information->argc == 1)
	{
		_eputs("Too few arguements.\n");
		return (1);
	}
	for (a = 1; a <= information->argc; a++)
		_unsetenv(information, information->argv[a]);

	return (0);
}

/**
 * populate_env_list - populate env lkd lst
 * @information: Structure has potent argmnt
 * Return: alw 0
 */
int populate_env_list(info_t *information)
{
	list_t *nde = NULL;
	size_t a;

	for (a = 0; environ[a]; a++)
		add_nde_end(&nde, environ[a], 0);
	information->env = nde;
	return (0);
}
