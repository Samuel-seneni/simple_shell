#include "shell.h"

/**
 * is_cmd - an executable command is determined
 * @info: the info struct
 * @path: path file
 * Return: 1 if true, 0 otherwise
 */
int is_cmd(info_t *info, char *path)
{
	struct stat h;

	(void)info;
	if (!path || stat(path, &h))
		return (0);

	if (h.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * dup_chars - characters to be dublicated
 * @path: the path string
 * @start: start of the index
 * @stop: end of the index
 * Return: buf
 */
char *dup_chars(char *path, int start, int stop)
{
	static char buf[1024];
	int x = 0; 
	int y = 0;

	for (y = 0, x = start; x < stop; x++)
		if (path[x] != ':')
			buf[y++] = path[x];
	buf[y] = 0;
	return (buf);
}

/**
 * find_path - finds path of string
 * @info: the info struct of the string
 * @str: the path string
 * @cmd: the command of the string
 * Return: full path of the command
 */
char *find_path(info_t *info, char *str, char *cmd)
{
	int x = 0;
	int p = 0;
	char *path;

	if (!str)
		return (NULL);
	if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (is_cmd(info, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!str[x] || str[x] == ':')
		{
			path = dup_chars(str, p, x);
			if (!*path)
				_strcat(path, cmd);
			else
			{
				_strcat(path, "/");
				_strcat(path, cmd);
			}
			if (is_cmd(info, path))
				return (path);
			if (!str[x])
				break;
			p = x;
		}
		x++;
	}
	return (NULL);
}
