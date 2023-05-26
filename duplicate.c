#include "shell.h"

/**
 * is_cmd - determines if a file is an executable command
 * @information: the information struct
 * @path: path to the file
 *
 * Return: 1 if true, 0 otherwise
 */
int is_cmd(info_t *information, char *path)
{
	struct stat st;

	(void)information;
	if (!path || stat(path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * dup_chars - duplicates characts
 * @pathstr: the PATH strg
 * @start: starting ind
 * @stop: stopping ind
 *
 * Return: pntr to new bf
 */
char *dup_chars(char *pathstr, int start, int stop)
{
	static char buff[1024];
	int a = 0, g = 0;

	for (g = 0, a = start; a < stop; a++)
		if (pathstr[a] != ':')
			buff[g++] = pathstr[a];
	buff[g] = 0;
	return (buff);
}

/**
 * find_path - fnds this cmd in the PATH strg
 * @information: the information struct
 * @pathstr: the PATH strg
 * @cmd: the cmd to find
 *
 * Return: full path of cmd if found or NULL
 */
char *find_path(info_t *information, char *pathstr, char *cmd)
{
	int a = 0, curr_pos = 0;
	char *path;

	if (!pathstr)
		return (NULL);
	if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (is_cmd(information, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathstr[a] || pathstr[a] == ':')
		{
			path = dup_chars(pathstr, curr_pos, a);
			if (!*path)
				_strcat(path, cmd);
			else
			{
				_strcat(path, "/");
				_strcat(path, cmd);
			}
			if (is_cmd(information, path))
				return (path);
			if (!pathstr[a])
				break;
			curr_pos = a;
		}
		a++;
	}
	return (NULL);
}
