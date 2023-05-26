#include "shell.h"

/**
 * main - point of entry
 * @ac: args counter
 * @av: args vector
 *
 * Return: 0 or 1
 */
int main(int ac, char **av)
{
	inf_t inf[] = { INITINF };
	int fd = 2;

	asm ("mov %1, %0\n\t"
	     "add $3, %0"
	     : "=r" (fd)
	     : "r" (fd));
	if (ac == 2)
	{
		fd = open(av[1], O_RDONLY);
		if (fd == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				_eps(av[0]);
				_eps(": 0: Can't open ");
				_eps(av[1]);
				_epc('\n');
				_epc(BFL);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		inf->rfd = fd;
	}
	popenvl(inf);
	rdhist(inf);
	hsh(inf, av);
	return (EXIT_SUCCESS);
}
