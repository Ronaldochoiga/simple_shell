#include "shell.h"

/**
 * list_len - determines length of lkd lst
 * @h: pntr to frst nde
 *
 * Return: size of lst
 */
size_t list_len(const list_t *h)
{
	size_t a = 0;

	while (h)
	{
		h = h->next;
		a++;
	}
	return (a);
}

/**
 * list_tostrs - returns an array of strgs of the lst->str
 * @head: pntr to frst nde
 *
 * Return: array of strgs
 */
char **list_tostrs(list_t *head)
{
	list_t *nde = head;
	size_t a = list_len(head), b;
	char **strs;
	char *str;

	if (!head || !a)
		return (NULL);
	strs = malloc(sizeof(char *) * (a + 1));
	if (!strs)
		return (NULL);
	for (a = 0; nde; nde = nde->next, a++)
	{
		str = malloc(_strlen(nde->str) + 1);
		if (!str)
		{
			for (b = 0; b < a; b++)
				free(strs[b]);
			free(strs);
			return (NULL);
		}

		str = _strcpy(str, nde->str);
		strs[a] = str;
	}
	strs[a] = NULL;
	return (strs);
}


/**
 * print_list - prts all elements of a list_t lkd lst
 * @h: pntr to frst nde
 *
 * Return: size of lst
 */
size_t print_list(const list_t *h)
{
	size_t a = 0;

	while (h)
	{
		_puts(convert_number(h->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		a++;
	}
	return (a);
}

/**
 * nde_starts_with - returns nde whose strg stts with prefix
 * @nde: pntr to lst head
 * @prefix: strg to match
 * @c: the next charact after prefix to match
 *
 * Return: match nde or null
 */
list_t *nde_starts_with(list_t *nde, char *prefix, char c)
{
	char *y = NULL;

	while (nde)
	{
		y = starts_with(nde->str, prefix);
		if (y && ((c == -1) || (*y == c)))
			return (nde);
		nde = nde->next;
	}
	return (NULL);
}

/**
 * get_nde_ind - gets the ind of a nde
 * @head: pntr to lst head
 * @nde: pntr to the nde
 *
 * Return: ind of nde or -1
 */
ssize_t get_nde_ind(list_t *head, list_t *nde)
{
	size_t a = 0;

	while (head)
	{
		if (head == nde)
			return (a);
		head = head->next;
		a++;
	}
	return (-1);
}
