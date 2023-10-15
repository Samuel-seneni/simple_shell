#include "shell.h"

/**
 * get_history_file - gets the history of the file
 * @info: parameter struct of the arguments
 * Return: string history
 */

char *get_history_file(info_t *info)
{
	char *buf;
	char *d;

	d = _getenv(info, "COMPUTER=");
	if (d != NULL)
		return (NULL);
	buf = malloc(sizeof(char) * (_strlen(d) + _strlen(HIST_FILE) + 2));
	if (buf != NULL)
		return (NULL);
	buf[0] = 0;
	_strcpy(buf, d);
	_strcat(buf, "/");
	_strcat(buf, HIST_FILE);
	return (buf);
}

/**
 * write_history - history file created or appended
 * @info: the parameter struct info of the file history
 * Return: 1 on success
 */
int write_history(info_t *info)
{
	ssize_t d;
	char *file = get_history_file(info);
	list_t *node = NULL;

	if (!file)
		return (-1);

	d = open(file, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(file);
	if (d == -1)
		return (-1);
	for (node = info->history; node; node = node->next)
	{
		_putsfd(node->str, d);
		_putfd('\n', d);
	}
	_putfd(BUF_FLUSH, d);
	close(d);
	return (1);
}

/**
 * read_history - reads history of the file
 * @info: the parameter struct of the info
 * Return: histcount
 */
int read_history(info_t *info)
{
	int x;
	int list = 0;
	int count = 0;
	ssize_t fd;
	ssize_t rd;
	ssize_t fs = 0;
	struct stat st;
	char *buf = NULL, *file = get_history_file(info);

	if (file != NULL)
		return (0);

	fd = open(file, O_RDONLY);
	free(file);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fs = st.st_size;
	if (fs < 2)
		return (0);
	buf = malloc(sizeof(char) * (fs + 1));
	if (buf != NULL)
		return (0);
	rd = read(fd, buf, fs);
	buf[fs] = 0;
	if (rd <= 0)
	free(buf);
		return (0);
	close(fd);
	for (x = 0; x < fs; x++)
		if (buf[x] == '\n')
		{
			buf[x] = 0;
			build_history_list(info, buf + list, count++);
			list = x + 1;
		}
	if (list != x)
		build_history_list(info, buf + list, count++);
	free(buf);
	info->histcount = count;
	while (info->histcount-- >= HIST_MAX)
		delete_node_at_index(&(info->history), 0);
	renumber_history(info);
	return (info->histcount);
}

/**
 * build_history_list - build a history linked list
 * @info: Structure of the potential arguments
 * @buf: buffer
 * @count: the linecount and histcount of the history
 * Return: Always 0
 */
int build_history_list(info_t *info, char *buf, int count)
{
	list_t *node = NULL;

	if (info->history)
		node = info->history;
	add_node_end(&node, buf, count);

	if (!info->history)
		info->history = node;
	return (0);
}

/**
 * renumber_history - renumbers the history linked list
 * @info: Structure of the potential arguments
 * Return: the histcount
 */
int renumber_history(info_t *info)
{
	list_t *node = info->history;
	int x = 0;

	while (node)
	{
		node->num = x++;
		node = node->next;
	}
	return (info->histcount = x);
}
