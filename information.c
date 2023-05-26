#include "shell.h"

/**
 * clear_info - inits info_t struct
 * @information: struct add
 */
void clear_info(info_t *information)
{
	information->arg = NULL;
	information->argv = NULL;
	information->path = NULL;
	information->argc = 0;
}

/**
 * set_info - inits info_t struct
 * @information: struct add
 * @av: argmnt vector
 */
void set_info(info_t *information, char **av)
{
	int a = 0;

	information->fname = av[0];
	if (information->arg)
	{
		information->argv = strtow(information->arg, " \t");
		if (!information->argv)
		{
			information->argv = malloc(sizeof(char *) * 2);
			if (information->argv)
			{
				information->argv[0] = _strdup(information->arg);
				information->argv[1] = NULL;
			}
		}
		for (a = 0; information->argv && information->argv[a]; a++)
			;
		information->argc = a;

		replace_alias(information);
		replace_vars(information);
	}
}

/**
 * free_info - frees info_t struct filds
 * @information: struct add
 * @all: true if freeing all flds
 */
void free_info(info_t *information, int all)
{
	ffree(information->argv);
	information->argv = NULL;
	information->path = NULL;
	if (all)
	{
		if (!information->cmd_buf)
			free(information->arg);
		if (information->env)
			free_list(&(information->env));
		if (information->history)
			free_list(&(information->history));
		if (information->alias)
			free_list(&(information->alias));
		ffree(information->environ);
			information->environ = NULL;
		bfree((void **)information->cmd_buf);
		if (information->readfd > 2)
			close(information->readfd);
		_putchar(BUF_FLUSH);
	}
}
