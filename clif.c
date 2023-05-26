#include "shell.h"

/**
 * clif - inits inf_t struct
 * @inf: structural address
 **/
void clif(inf_t *inf)
{
	inf->arg = NULL;
	inf->argv = NULL;
	inf->pth = NULL;
	inf->argc = 0;
}

/**
 * setin - inits inf_t structure
 * @inf: structural address
 * @av: argument vector
 */
void setin(inf_t *inf, char **av)
{
	int j = 0;

	inf->fname = av[0];
	if (inf->arg)
	{
		inf->argv = strtow(inf->arg, " \t");
		if (!inf->argv)
		{
			inf->argv = malloc(sizeof(char *) * 2);
			if (inf->argv)
			{
				inf->argv[0] = _strdup(inf->arg);
				inf->argv[1] = NULL;
			}
		}
		for (j = 0; inf->argv && inf->argv[j]; j++)
			;
		inf->argc = j;
		repalias(inf);
		repvrs(inf);
	}
}

/**
 * frinf - free inf_t structure fields
 * @inf: structural address
 * @all: truth for freeing all fields
 */
void frinf(inf_t *inf, int all)
{
	ffr(inf->argv);
	inf->argv = NULL;
	inf->pth = NULL;
	if (all)
	{
		if (!inf->cbuf)
			free(inf->arg);
		if (inf->env)
			free_l(&(inf->env));
		if (inf->hist)
			free_l(&(inf->hist));
		if (inf->alias)
			free_l(&(inf->alias));
		ffr(inf->environ);
		inf->environ = NULL;
		bfree((void **)inf->cbuf);
		if (inf->rfd > 2)
			close(inf->rfd);
		_putchar(BFL);
	}
}
