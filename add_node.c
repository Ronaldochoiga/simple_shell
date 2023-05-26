#include "shell.h"

/**
 * add_nde - add nde to start of str
 * @head: address of pointer to head
 * @str: str field of nde
 * @num: nde ind used by hist
 *
 * Return: sze of the list
 */
lt *add_nde(lt **head, consize_t char *str, int num)
{
	lt *newd;

	if (!head)
		return (NULL);
	newd = malloc(sizeof(lt));
	if (!newd)
		return (NULL);
	_memset((void *)newd, 0, sizeof(lt));
	newd->num = num;
	if (str)
	{
		newd->str = _strdup(str);
		if (!newd->str)
		{
			free(newd);
			return (NULL);
		}
	}
	newd->next = *head;
	*head = newd;
	return (newd);
}

/**
 * add_end - adds nodfe to listend
 * @head: address of pointer headnde
 * @str: str field of the nde
 * @num: nde ind used by hist
 *
 * Return: sze of lst
 */
lt *add_end(lt **head, const char *str, int num)
{
	lt *new_nde, *nde;

	if (!head)
		return (NULL);

	nde = *head;
	new_nde = malloc(sizeof(lt));
	if (!new_nde)
		return (NULL);
	_memset((void *)new_nde, 0, sizeof(lt));
	new_nde->num = num;
	if (str)
	{
		new_nde->str = _strdup(str);
		if (!new_nde->str)
		{
			free(new_nde);
			return (NULL);
		}
	}
	if (nde)
	{
		while (nde->next)
			nde = nde->next;
		nde->next = new_nde;
	}
	else
		*head = new_nde;
	return (new_nde);
}

/**
 * plstr - prints only the str element of a lt linked list
 * @h: firstnde pointer
 *
 * Return: liat==size_t size
 */
size_t plstr(const lt *h)
{
	size_t j = 0;

	while (h)
	{
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		j++;
	}
	return (j);
}

/**
 * del_ind - del nde at given ind
 * @head: firsize_t nde popinter address
 * @ind: ind of nde to del
 *
 * Return: 1 or 0
 */
int del_ind(lt **head, unsigned int ind)
{
	lt *nde, *prev_nde;
	unsigned int i = 0;

	if (!head || !*head)
		return (0);

	if (!ind)
	{
		nde = *head;
		*head = (*head)->next;
		free(nde->str);
		free(nde);
		return (1);
	}
	nde = *head;
	while (nde)
	{
		if (i == ind)
		{
			prev_nde->next = nde->next;
			free(nde->str);
			free(nde);
			return (1);
		}
		i++;
		prev_nde = nde;
		nde = nde->next;
	}
	return (0);
}
/**
 * free_l - frees ndes of a list
 * @hqtr: addr of head nde pointer
 *
 * Return: void
 */
void free_l(lt **hqtr)
{
	lt *nde, *next_nde, *head;

	if (!hqtr || !*hqtr)
		return;
	head = *hqtr;
	nde = head;
	while (nde)
	{
		next_nde = nde->next;
				free(nde->str);
				free(nde);
				nde = next_nde;
	}
	*hqtr = NULL;
}
