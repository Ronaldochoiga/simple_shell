#include "shell.h"

/**
 * add_nde - adds a nde to the start of the lst
 * @head: add of pntr to head nde
 * @str: str fild of nde
 * @num: nde ind used by history
 *
 * Return: size of lst
 */
list_t *add_nde(list_t **head, const char *str, int num)
{
	list_t *new_head;

	if (!head)
		return (NULL);
	new_head = malloc(sizeof(list_t));
	if (!new_head)
		return (NULL);
	_memset((void *)new_head, 0, sizeof(list_t));
	new_head->num = num;
	if (str)
	{
		new_head->str = _strdup(str);
		if (!new_head->str)
		{
			free(new_head);
			return (NULL);
		}
	}
	new_head->next = *head;
	*head = new_head;
	return (new_head);
}

/**
 * add_nde_end - adds a nde to the end of the lst
 * @head: add of pntr to head nde
 * @str: str fild of nde
 * @num: nde ind used by history
 *
 * Return: size of lst
 */
list_t *add_nde_end(list_t **head, const char *str, int num)
{
	list_t *new_nde, *nde;

	if (!head)
		return (NULL);

	nde = *head;
	new_nde = malloc(sizeof(list_t));
	if (!new_nde)
		return (NULL);
	_memset((void *)new_nde, 0, sizeof(list_t));
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
 * print_list_str - prts only the str element of a list_t lkd lst
 * @h: pntr to frst nde
 *
 * Return: size of lst
 */
size_t print_list_str(const list_t *h)
{
	size_t a = 0;

	while (h)
	{
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		a++;
	}
	return (a);
}

/**
 * delete_nde_at_ind - deletes nde at given ind
 * @head: add of pntr to frst nde
 * @ind: ind of nde to delete
 *
 * Return: 1 on success, 0 on failure
 */
int delete_nde_at_ind(list_t **head, unsigned int ind)
{
	list_t *nde, *prev_nde;
	unsigned int a = 0;

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
		if (a == ind)
		{
			prev_nde->next = nde->next;
			free(nde->str);
			free(nde);
			return (1);
		}
		a++;
		prev_nde = nde;
		nde = nde->next;
	}
	return (0);
}

/**
 * free_list - frees all ndes of a lst
 * @head_ptr: add of pntr to head nde
 *
 * Return: void
 */
void free_list(list_t **head_ptr)
{
	list_t *nde, *next_nde, *head;

	if (!head_ptr || !*head_ptr)
		return;
	head = *head_ptr;
	nde = head;
	while (nde)
	{
		next_nde = nde->next;
		free(nde->str);
		free(nde);
		nde = next_nde;
	}
	*head_ptr = NULL;
}
