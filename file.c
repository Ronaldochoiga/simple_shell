#include "shell.h"

/**
 * get_history_file - gets the hist file
 * @information: param struct
 *
 * Return: alloctd strg containg history file
 */

char *get_history_file(info_t *information)
{
	char *buff, *dr;

	dr = _gtenv(information, "HOME=");
	if (!dr)
		return (NULL);
	buff = malloc(sizeof(char) * (_strlen(dr) + _strlen(HIST_FILE) + 2));
	if (!buff)
		return (NULL);
	buff[0] = 0;
	_strcpy(buff, dr);
	_strcat(buff, "/");
	_strcat(buff, HIST_FILE);
	return (buff);
}

/**
 * write_history - creates or appends to existing file
 * @information: the param struct
 *
 * Return: 1 on success, else -1
 */
int write_history(info_t *information)
{
	ssize_t fd;
	char *filename = get_history_file(information);
	list_t *nde = NULL;

	if (!filename)
		return (-1);

	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fd == -1)
		return (-1);
	for (nde = information->history; nde; nde = nde->next)
	{
		_putsfd(nde->str, fd);
		_putfd('\n', fd);
	}
	_putfd(BUF_FLUSH, fd);
	close(fd);
	return (1);
}

/**
 * read_history - reads history from file
 * @information: the param struct
 *
 * Return: histcount on success, 0 otherwise
 */
int read_history(info_t *information)
{
	int a, last = 0, linecount = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *buff = NULL, *filename = get_history_file(information);

	if (!filename)
		return (0);

	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buff = malloc(sizeof(char) * (fsize + 1));
	if (!buff)
		return (0);
	rdlen = read(fd, buff, fsize);
	buff[fsize] = 0;
	if (rdlen <= 0)
		return (free(buff), 0);
	close(fd);
	for (a = 0; a < fsize; a++)
		if (buff[a] == '\n')
		{
			buff[a] = 0;
			build_history_list(information, buff + last, linecount++);
			last = a + 1;
		}
	if (last != a)
		build_history_list(information, buff + last, linecount++);
	free(buff);
	information->histcount = linecount;
	while (information->histcount-- >= HIST_MAX)
		delete_nde_at_ind(&(information->history), 0);
	renumber_history(information);
	return (information->histcount);
}

/**
 * build_history_list - adds entry to a history lkd lst
 * @information: Structure containing potent argmnt. Used to maintain
 * @buff: bf
 * @linecount: the history linecount, histcount
 *
 * Return: alw 0
 */
int build_history_list(info_t *information, char *buff, int linecount)
{
	list_t *nde = NULL;

	if (information->history)
		nde = information->history;
	add_nde_end(&nde, buff, linecount);

	if (!information->history)
		information->history = nde;
	return (0);
}

/**
 * renumber_history - renumbers the history lkd lst after changes
 * @information: Structure containing potent argmnt.
 *
 * Return: the new histcount
 */
int renumber_history(info_t *information)
{
	list_t *nde = information->history;
	int a = 0;

	while (nde)
	{
		nde->num = a++;
		nde = nde->next;
	}
	return (information->histcount = a);
}
