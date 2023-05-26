#include "shell.h"

/**
 * _mxt - exit shell
 * @inf: Struct has potent args
 * Return: exit with a given phrase
 */
int _mxt(inf_t *inf)
{
	int exitch;

	if (inf->argv[1])
	{
		exitch = _errstoi(inf->argv[1]);
		if (exitch == -1)
		{
			inf->sts = 2;
			printer(inf, "Illegal number: ");
			_eps(inf->argv[1]);
			_epc('\n');
			return (1);
		}
		inf->errn = _errstoi(inf->argv[1]);
		return (-2);
	}
	inf->errn = -1;
	return (-2);
}

/**
 * _md - change current cd
 * @inf: Struct has potential args
 * Return: Always zero
 */
int _md(inf_t *inf)
{
	char *s, *d, buff[1024];
	int cdr;

	s = getcwd(buff, 1024);
	if (!s)
		_puts("TODO: >>getcwd failure message here<<\n");
	if (!inf->argv[1])
	{
		d = gev(inf, "HOME=");
		if (!d)
			cdr =/*TODO: what is this*/
				chdir((d = gev(inf, "PDIR=")) ? d : "/");
		else
			cdr = chdir(d);
	}
	else if (_strcmp(inf->argv[1], "-") == 0)
	{
		if (!gev(inf, "OLDPDIR="))
		{
			_puts(s);
			_putchar('\n');
			return (1);
		}
		_puts(gev(inf, "OLDPDIR=")), _putchar('\n');
		cdr = /* TODO: what is this*/
			chdir((d = gev(inf, "OLDPDIR=")) ? d : "/");
	}
	else
		cdr = chdir(inf->argv[1]);
	if (cdr == -1)
	{
		printer(inf, "can't cd to ");
		_eps(inf->argv[1]), _epc('\n');
	}
	else
	{
		_sev(inf, "OLDPDIR", gev(inf, "PDIR="));
		_sev(inf, "PDIR", getcwd(buff, 1024));
	}
	return (0);
}

/**
 * _myhp - changes currents dir toanother dir
 * @inf: Struct has potent args
 * Return: Always zero
 */
int _myhp(inf_t *inf)
{
	char **argar;

	argar = inf->argv;
	_puts("help call works. Function not implemented \n");
	if (0)
		_puts(*argar);
	return (0);
}
