#include "shell.h"

/**
 * main - entry point
 * @ac: arg count
 * @av: arg vector
 *
 * Return: 0 on success, 1 on error
 */
int main(int ac, char **av)
{
	info_t information[] = { INFO_INIT };
	int fd = 2;

	asm ("mov %1, %0\n\t"
	     "add $3, %0"
	     : "=r" (fd)
	     : "r" (fd)
		);

	if (ac == 2)
	{
		fd = open(av[1], O_RDONLY);
		if (fd == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				_eputs(av[0]);
				_eputs(": 0: Can't open ");
				_eputs(av[1]);
				_eputchar('\n');
				_eputchar(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		information->readfd = fd;
	}
	populate_env_list(information);
	read_history(information);
	hsh(information, av);
	return (EXIT_SUCCESS);
}

/**
 * bfree - frees a pntr and NULLs the add
 * @ptr: add of the pntr to free
 *
 * Return: 1 if freed, otherwise 0.
 */
int bfree(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}
