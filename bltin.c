#include "shell.h"

/**
 * _ourexit - exit shell
 * @information: Structure has potent argmnt
 * Return: ext with argv or -2
 */
int _ourexit(info_t *information)
{
	int exitcheck;

	if (information->argv[1]) /* If there is an exit arguement */
	{
		exitcheck = _erratoi(information->argv[1]);
		if (exitcheck == -1)
		{
			information->status = 2;
			print_error(information, "Illegal numb: ");
			_eputs(information->argv[1]);
			_eputchar('\n');
			return (1);
		}
		information->err_num = _erratoi(information->argv[1]);
		return (-2);
	}
	information->err_num = -1;
	return (-2);
}

/**
 * _ourcd - change curr direct
 * @information: Structure  has potent argmnt
 * Return: alw zero
 */
int _ourcd(info_t *information)
{
	char *s, *dr, bf[1024];
	int chret;

	s = getcwd(bf, 1024);
	if (!s)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!information->argv[1])
	{
		dr = _gtenv(information, "HOME=");
		if (!dr)
			chret = /* TODO: what should this be? */
				chdir((dr = _gtenv(information, "PWD=")) ? dr : "/");
		else
			chret = chdir(dr);
	}
	else if (_strcmp(information->argv[1], "-") == 0)
	{
		if (!_gtenv(information, "OLDPWD="))
		{
			_puts(s);
			_putchar('\n');
			return (1);
		}
		_puts(_gtenv(information, "OLDPWD=")), _putchar('\n');
		chret = /* TODO: what should this be? */
			chdir((dr = _gtenv(information, "OLDPWD=")) ? dr : "/");
	}
	else
		chret = chdir(information->argv[1]);
	if (chret == -1)
	{
		print_error(information, "can't cd to ");
		_eputs(information->argv[1]), _eputchar('\n');
	}
	else
	{
		_setenv(information, "OLDPWD", _gtenv(information, "PWD="));
		_setenv(information, "PWD", getcwd(bf, 1024));
	}
	return (0);
}
/**
 * _ourhelp - changes curr direct
 * @information: Structure has potent argmnt
 * Return: alw 0
 */
int _ourhelp(info_t *information)
{
	char **arg_array;

	arg_array = information->argv;
	_puts("help call works. fnct not yet implemented \n");
	if (0)
		_puts(*arg_array);
	return (0);
}
