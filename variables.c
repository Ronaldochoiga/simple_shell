#include "shell.h"

/**
 * is_chain - test whether curr char in bf is chain delim
 * @information: the param struct
 * @buff: the char bf
 * @y: add of curr pos in buff
 *
 * Return: 1 or 0
 */
int is_chain(info_t *information, char *buff, size_t *y)
{
	size_t b = *y;

	if (buff[b] == '|' && buff[b + 1] == '|')
	{
		buff[b] = 0;
		b++;
		information->cmd_buf_type = CMD_OR;
	}
	else if (buff[b] == '&' && buff[b + 1] == '&')
	{
		buff[b] = 0;
		b++;
		information->cmd_buf_type = CMD_AND;
	}
	else if (buff[b] == ';')
	{
		buff[b] = 0;
		information->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*y = b;
	return (1);
}

/**
 * check_chain - check whether to proceed chaining
 * @information: the param struct
 * @buff: the char bf
 * @y: add of curr pos in buff
 * @a: starting pos in buff
 * @len: length of buff
 *
 * Return: Void
 */
void check_chain(info_t *information, char *buff, size_t *y, size_t a, size_t len)
{
	size_t b = *y;

	if (information->cmd_buf_type == CMD_AND)
	{
		if (information->status)
		{
			buff[a] = 0;
			b = len;
		}
	}
	if (information->cmd_buf_type == CMD_OR)
	{
		if (!information->status)
		{
			buff[a] = 0;
			b = len;
		}
	}

	*y = b;
}

/**
 * replace_alias - replaces alias in str
 * @information: the param struct
 *
 * Return: 1 or 0
 */
int replace_alias(info_t *information)
{
	int a;
	list_t *nde;
	char *y;

	for (a = 0; a < 10; a++)
	{
		nde = nde_starts_with(information->alias, information->argv[0], '=');
		if (!nde)
			return (0);
		free(information->argv[0]);
		y = _strchr(nde->str, '=');
		if (!y)
			return (0);
		y = _strdup(y + 1);
		if (!y)
			return (0);
		information->argv[0] = y;
	}
	return (1);
}

/**
 * replace_vars - replaces vars in the tokenized strg
 * @information: the param struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_vars(info_t *information)
{
	int a = 0;
	list_t *nde;

	for (a = 0; information->argv[a]; a++)
	{
		if (information->argv[a][0] != '$' || !information->argv[a][1])
			continue;

		if (!_strcmp(information->argv[a], "$?"))
		{
			replacestr(&(information->argv[a]),
					_strdup(convert_number(information->status, 10, 0)));
			continue;
		}
		if (!_strcmp(information->argv[a], "$$"))
		{
			replacestr(&(information->argv[a]),
					_strdup(convert_number(getpid(), 10, 0)));
			continue;
		}
		nde = nde_starts_with(information->env, &information->argv[a][1], '=');
		if (nde)
		{
			replacestr(&(information->argv[a]),
					_strdup(_strchr(nde->str, '=') + 1));
			continue;
		}
		replacestr(&information->argv[a], _strdup(""));

	}
	return (0);
}

/**
 * replacestr - replaces strg
 * @old: add of old strg
 * @new: new strg
 *
 * Return: 1 or 0
 */
int replacestr(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}
