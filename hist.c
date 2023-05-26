#include "shell.h"

/**
 * ghf - gets hist file
 * @inf: functional parameter
 *
 * Return: alloc str with hist fle
 */

char *ghf(inf_t *inf)
{
	char *buf, *d;

	d = gev(inf, "HOME=");
	if (!d)
		return (NULL);
	buf = malloc(sizeof(char) * (_strlen(d) + _strlen(HISTFLE) + 2));
	if (!buf)
		return (NULL);
	buf[0] = 0;
	_strcpy(buf, d);
	_strcat(buf, "/");
	_strcat(buf, HISTFLE);
	return (buf);
}

/**
 * write_hist - creates a file
 * @inf: structural parameter
 *
 * Return: 1 or -1
 */
int write_hist(inf_t *inf)
{
	ssize_t fd;
	char *fnme = ghf(inf);
	lt *nde = NULL;

	if (!fnme)
		return (-1);
	fd = open(fnme, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(fnme);
	if (fd == -1)
		return (-1);
	for (nde = inf->hist; nde; nde = nde->next)
	{
		_psfd(nde->str, fd);
		_ptfd('\n', fd);
	}
	_ptfd(BFL, fd);
	close(fd);
	return (1);
}

/**
 * rdhist - reads hist
 * @inf: fuctional parameter
 *
 * Return: hcnt or zero
 */
int rdhist(inf_t *inf)
{
	int j, l = 0, lcnt = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *buf = NULL, *fnme = ghf(inf);

	if (!fnme)
		return (0);
	fd = open(fnme, O_RDONLY);
	free(fnme);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buf = malloc(sizeof(char) * (fsize + 1));
	if (!buf)
		return (0);
	rdlen = read(fd, buf, fsize);
	buf[fsize] = 0;
	if (rdlen <= 0)
		return (free(buf), 0);
	close(fd);
	for (j = 0; j < fsize; j++)
		if (buf[j] == '\n')
		{
			buf[i] = 0;
			bhl(inf, buf + l, lcnt++);
			l = j + 1;
		}
	if (l != j)
		bhl(inf, buf + l, lcnt++);
	free(buf);
	inf->hcnt = lcnt;
	while (inf->hcnt-- >= HMAX)
		del_ind(&(inf->hist), 0);
	renum_hist(inf);
	return (inf->hcnt);
}

/**
 * bhl - adds entry point to a hist
 * @inf: Struct with potential args
 * @buf: buff
 * @lcnt: the hist lcnt, hcnt
 *
 * Return: Always zero
 */
int bhl(inf_t *inf, char *buf, int lcnt)
{
	lt *nde = NULL;

	if (inf->hist)
		nde = inf->hist;
	add_end(&nde, buf, lcnt);
	if (!inf->hist)
		inf->hist = nde;
	return (0);
}
/**
 * renum_hist - renums the hist after changes
 * @inf: Struct with potent args
 *
 * Return: new hcnt
 */
int renum_hist(inf_t *inf)
{
	lt *nde = inf->hist;
	int j = 0;

	while (nde)
	{
		nde->num = j++;
		nde = nde->next;
	}
	return (inf->hcnt = j);
}