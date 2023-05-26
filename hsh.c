#include "shell.h"

/**
 * hsh - main loop
 * @inf: fp
 * @av: arg vector main()
 *
 * Return: 0, 1 or error code
 */
int hsh(inf_t *inf, char **av)
{
	ssize_t r = 0;
	int blin_ret = 0;

	while (r != -1 && blin_ret != -2)
	{
		clif(inf);
		if (interactive(inf))
			_puts("$ ");
		_epc(BFL);
		r = get_in(inf);
		if (r != -1)
		{
			setin(inf, av);
			blin_ret = find_blin(inf);
			if (blin_ret == -1)
				fcmd(inf);
		}
		else if (interactive(inf))
			_putchar('\n');
		frinf(inf, 0);
	}
	write_hist(inf);
	frinf(inf, 1);
	if (!interactive(inf) && inf->sts)
		exit(inf->sts);
	if (blin_ret == -2)
	{
		if (inf->errn == -1)
			exit(inf->sts);
		exit(inf->errn);
	}
	return (blin_ret);
}

/**
 * find_blin - finds a blin comm
 * @inf: fp
 *
 * Return: -1, 0, 1, 2,
 */
int find_blin(inf_t *inf)
{
	int i, bl_in_ret = -1;
	blin_table blintbl[] = {
		{"exit", _mxt},
		{"env", _myv},
		{"help", _myhp},
		{"hist", _myhist},
		{"sev", _mysev},
		{"unsev", _myunsev},
		{"cd", _md},
		{"alias", _myal},
		{NULL, NULL}
	};

	for (i = 0; blintbl[i].type; i++)
		if (_strcmp(inf->argv[0], blintbl[i].type) == 0)
		{
			inf->linco++;
			bl_in_ret = blintbl[i].func(inf);
			break;
		}
	return (bl_in_ret);
}

/**
 * fcmd - gets command from pth
 * @inf: fp
 *
 * Return: void
 */
void fcmd(inf_t *inf)
{
	char *pth = NULL;
	int j, l;

	inf->pth = inf->argv[0];
	if (inf->linecofg == 1)
	{
		inf->linco++;
		inf->linecofg = 0;
	}
	for (j = 0, l = 0; inf->arg[j]; j++)
		if (!is_delim(inf->arg[j], " \t\n"))
			l++;
	if (!l)
		return;
	pth = fpth(inf, gev(inf, "PTH="), inf->argv[0]);
	if (pth)
	{
		inf->pth = pth;
		forkcd(inf);
	}
	else
	{
		if ((interactive(inf) || gev(inf, "PTH=")
		     || inf->argv[0][0] == '/') && icmd(inf, inf->argv[0]))
			forkcd(inf);
		else if (*(inf->arg) != '\n')
		{
			inf->sts = 127;
			printer(inf, "not found\n");
		}
	}
}
/**
 * forkcd - makes exec thread to be run
 * @inf: struct parameter
 *
 * Return: void
 */
void forkcd(inf_t *inf)
{
	pdt chdpd;

	chdpd = fork();
	if (chdpd == -1)
	{
		perror("Error:");
		return;
	}
	if (chdpd == 0)
	{
		if (execve(inf->pth, inf->argv, get_environ(inf)) == -1)
		{
			frinf(inf, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(inf->sts));
		if (WIFEXITED(inf->sts))
		{
			inf->sts = WEXITSTS(inf->sts);
			if (inf->sts == 126)
				printer(inf, "Permission denied\n");
		}
	}
}
