#include "shell.h"

/**
 * icmd - determines if is executable
 * @inf: the inf structure
 * @pth: file pth
 *
 * Return: 1 or zero
 */
int icmd(inf_t *inf, char *pth)
{
	struct stat st;

	(void)inf;
	if (!pth || stat(pth, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * chardup - duplicates chars
 * @pthstr: the PTH str
 * @start: starting ind
 * @stop: stopping ind
 *
 * Return: new_bufferint pointer
 */
char *chardup(char *pthstr, int start, int stop)
{
	static char buf[1024];
	int j = 0, l = 0;

	for (l = 0, j = start; j < stop; j++)
		if (pthstr[j] != ':')
			buf[l++] = pthstr[j];
	buf[l] = 0;
	return (buf);
}

/**
 * fpth - finds cmd in str
 * @inf: the inf structure
 * @pthstr: PTH str
 * @cmd: cmd to find
 *
 * Return: pth or NULL
 */
char *fpth(inf_t *inf, char *pthstr, char *cmd)
{
	int j = 0, curpos = 0;
	char *pth;

	if (!pthstr)
		return (NULL);
	if ((_strlen(cmd) > 2) && sw(cmd, "./"))
	{
		if (icmd(inf, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pthstr[j] || pthstr[j] == ':')
		{
			pth = chardup(pthstr, curpos, j);
			if (!*pth)
				_strcat(pth, cmd);
			else
			{
				_strcat(pth, "/");
				_strcat(pth, cmd);
			}
			if (icmd(inf, pth))
				return (pth);
			if (!pthstr[j])
				break;
			curpos = j;
		}
		j++;
	}
	return (NULL);
}
