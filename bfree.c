#include "shell.h"

/**
 * bfree - frees pointers and makes the addr NULL
 * @qtr: add of pointer to be freed
 *
 * Return: 0 or 1
 */
int bfree(void **qtr)
{
	if (qtr && *qtr)
	{
		free(*qtr);
		*qtr = NULL;
		return (1);
	}
	return (0);
}
