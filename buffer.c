#include "shell.h"

/**
 * input_buf - bfs chained commands
 * @information: param struct
 * @buff: add of bf
 * @len: add of len var
 *
 * Return: bytes read
 */
ssize_t input_buf(info_t *information, char **buff, size_t *len)
{
	ssize_t z = 0;
	size_t len_p = 0;

	if (!*len) /* if nothing left in the bf, fill it */
	{
		/*bfree((void **)information->cmd_buf);*/
		free(*buff);
		*buff = NULL;
		signal(SIGINT, sigintHandler);
#if USE_gtLINE
		z = getline(buff, &len_p, stdin);
#else
		z = _gtline(information, buff, &len_p);
#endif
		if (z > 0)
		{
			if ((*buff)[z - 1] == '\n')
			{
				(*buff)[z - 1] = '\0'; /* remove trailing newline */
				z--;
			}
			information->linecount_flag = 1;
			remove_comments(*buff);
			build_history_list(information, *buff, information->histcount++);
			/* if (_strchr(*buff, ';')) is this a command chain? */
			{
				*len = z;
				information->cmd_buf = buff;
			}
		}
	}
	return (z);
}

/**
 * get_input - gets a line minus the newline
 * @information: param struct
 *
 * Return: bytes read
 */
ssize_t get_input(info_t *information)
{
	static char *buff; /* the ';' command chain bf */
	static size_t a, b, len;
	ssize_t z = 0;
	char **buf_p = &(information->arg), *y;

	_putchar(BUF_FLUSH);
	z = input_buf(information, &buff, &len);
	if (z == -1) /* EOF */
		return (-1);
	if (len) /* we have commands left in the chain bf */
	{
		b = a; /* init new iterator to curr buff position */
		y = buff + a; /* get pntr for return */

		check_chain(information, buff, &b, a, len);
		while (b < len) /* iterate to semicolon or end */
		{
			if (is_chain(information, buff, &b))
				break;
			b++;
		}

		a = b + 1;
		if (a >= len)
		{
			a = len = 0;
			information->cmd_buf_type = CMD_NORM;
		}

		*buf_p = y;
		return (_strlen(y));
	}

	*buf_p = buff;
	return (z);
}

/**
 * read_buf - reads a bf
 * @information: param struct
 * @buff: bf
 * @a: size
 *
 * Return: z
 */
ssize_t read_buf(info_t *information, char *buff, size_t *a)
{
	ssize_t z = 0;

	if (*a)
		return (0);
	z = read(information->readfd, buff, READ_BUF_SIZE);
	if (z >= 0)
		*a = z;
	return (z);
}

/**
 * _gtline - gets the next line of input from STDIN
 * @information: param struct
 * @ptr: add of pntr
 * @length: size of prealloctd ptr bf if not NULL
 *
 * Return: s
 */
int _gtline(info_t *information, char **ptr, size_t *length)
{
	static char buff[READ_BUF_SIZE];
	static size_t a, len;
	size_t g;
	ssize_t z = 0, s = 0;
	char *y = NULL, *new_p = NULL, *c;

	y = *ptr;
	if (y && length)
		s = *length;
	if (a == len)
		a = len = 0;

	z = read_buf(information, buff, &len);
	if (z == -1 || (z == 0 && len == 0))
		return (-1);

	c = _strchr(buff + a, '\n');
	g = c ? 1 + (unsigned int)(c - buff) : len;
	new_p = _realloc(y, s, s ? s + g : g + 1);
	if (!new_p) /* MALLOC FAILURE! */
		return (y ? free(y), -1 : -1);

	if (s)
		_strncat(new_p, buff + a, g - a);
	else
		_strncpy(new_p, buff + a, g - a + 1);

	s += g - a;
	a = g;
	y = new_p;

	if (length)
		*length = s;
	*ptr = y;
	return (s);
}

/**
 * sigintHandler - blocks ctrl-C
 * @sig_num: the signal numb
 *
 * Return: void
 */
void sigintHandler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}
