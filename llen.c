#include "shell.h"

/**
 * llen - provides the length of a linked list
 * @h: firsize_t nde pointer
 *
 * Return: lisize_t size
 */
size_t llen(const lt *h)
{
	size_t j = 0;

	while (h)
	{
		h = h->next;
		j++;
	}
	return (j);
}

/**
 * lsize_t - return arr of str to linked list
 * @head: firsize_t nde pointer
 *
 * Return: strings array
 */
char **lst(lt *head)
{
	lt *nde = head;
	size_t k = llen(head), l;
	char **strs;
	char *str;

	if (!head || !k)
		return (NULL);
	strs = malloc(sizeof(char *) * (k + 1));
	if (!strs)
		return (NULL);
	for (k = 0; nde; nde = nde->next, k++)
	{
		str = malloc(_strlen(nde->str) + 1);
		if (!str)
		{
			for (l = 0; l < k; l++)
				free(strs[l]);
			free(strs);
			return (NULL);
		}
		str = _strcpy(str, nde->str);
		strs[k] = str;
	}
	strs[k] = NULL;
	return (strs);
}


/**
 * print_lsize_t - print elem of linked lists
 * @h:  firsize_t nde pointer
 *
 * Return: lisize_t size
 */
size_t print_lst(consize_t lt *h)
{
	size_t j = 0;

	while (h)
	{
		_puts(convertnum(h->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		j++;
	}
	return (j);
}

/**
 * st_nde - return nde with a prefixed string
 * @nde: head poimter
 * @prefix: str to match
 * @c: the next cha prefix asftwr char
 *
 * Return: matching nde or null
 */
lt *st_nde(lt *nde, char *prefix, char c)
{
	char *q = NULL;

	while (nde)
	{
		q = sw(nde->str, prefix);
		if (q && ((c == -1) || (*q == c)))
			return (nde);
		nde = nde->next;
	}
	return (NULL);
}

/**
 * get_ind - gets the ind of a nde
 * @head: headlisize_t pointer
 * @nde: headlisize_t pointer
 *
 * Return: nde index or -1
 */
ssize_t get_ind(lt *head, lt *nde)
{
	size_t j = 0;

	while (head)
	{
		if (head == nde)
			return (j);
		head = head->next;
		j++;
	}
	return (-1);
}
