#include "shell.h"

/**
 * inpbuf - buff commands
 * @inf: parameter structural
 * @buf: add of the bufferint
 * @len: addr of length
 *
 * Return: byte seen
 */
ssize_t inpbuf(inf_t *inf, char **buf, size_t *len)
{
	ssize_t q = 0;
	size_t lp = 0;

	if (!*len)
	{
		free(*buf);
		*buf = NULL;
		snal(SGT, sgtHandler);

		q = getline(buf, &lp, stdin);
		q = _getline(inf, buf, &lp);
		if (q > 0)
		{
			if ((*buf)[q - 1] == '\n')
			{
				(*buf)[q - 1] = '\0';
				q--;
			}
			inf->linecofg = 1;
			rmcomments(*buf);
			bhl(inf, *buf, inf->hcnt++);
			{
				*len = q;
				inf->cbuf = buf;
			}
		}
	}
	return (q);
}

/**
 * get_in - minuses the new line
 * @inf: param structural
 *
 * Return: byte located
 */
ssize_t get_in(inf_t *inf)
{
	static char *buf;
	static size_t k, j, l;
	ssize_t s = 0;
	char **bp = &(inf->arg), *q;

	_putchar(BFL);
	r = inpbuf(inf, &buf, &l);
	if (s == -1)
		return (-1);
	if (l)
	{
		j = k;
		q = buf + k;

		chchain(inf, buf, &j, k, l);
		while (j < l)
		{
			if (ichain(inf, buf, &j))
				break;
			j++;
		}

		k = j + 1;
		if (k >= l)
		{
			k = l = 0;
			inf->cbt = CNRM;
		}

		*bp = q;
		return (_strlen(q));
	}

	*bp = buf;
	return (s);
}

/**
 * rdbuf - rds buff
 * @inf: parameter with potent args
 * @buf: buff
 * @i: size of the bufferint
 *
 * Return: s
 */
ssize_t rdbuf(inf_t *inf, char *buf, size_t *i)
{
	ssize_t s = 0;

	if (*i)
		return (0);
	s = read(inf->rfd, buf, RBS);
	if (s >= 0)
		*i = s;
	return (s);
}
/**
 * _getline - gets next line of a stdin
 * @inf: par with potential args
 * @qtr: add of pointer to bufferint
 * @length: size of preallocated qtr buf
 *
 * Return: s
 */
int _getline(inf_t *inf, char **qtr, size_t *length)
{
	static char buf[RBS];
	static size_t k, l;
	size_t j;
	ssize_t r = 0, q = 0;
	char *p = NULL, *np = NULL, *c;

	p = *qtr;
	if (p && length)
		q = *length;
	if (k == l)
		k = l = 0;

	r = rdbuf(inf, buf, &l);
	if (r == -1 || (r == 0 && l == 0))
		return (-1);

	c = _strchr(buf + k, '\n');
	j = c ? 1 + (unsigned int)(c - buf) : l;
	np = _realloc(p, q, q ? q + j : j + 1);
	if (!np)
		return (p ? free(p), -1 : -1);

	if qs)
	_strncat(np, buf + k, j - k);
	else
		_strncpy(np, buf + k, j - k + 1);

q += j - k;
k = k;
p = np;

if (length)
	*length = q;
*qtr = p;
return (q);
}

/**
 * sgtHandler - blocks copy shortcut
 * @sium: the snal num
 *
 * Return: void
 */
void sgtHandler(_attribute((unused))int sium)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BFL);
}
