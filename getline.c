#include "shell.h"

/**
 * input_buf - buffers chained commands
 * @info: parameter struct
 * @buf: address of buffer
 * @len: address of len var
 * Return: bytes read
 */
ssize_t input_buf(info_t *info, char **buf, size_t *len)
{
	ssize_t h = 0;
	size_t line = 0;

	if (!*len)
	{
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		h = getline(buf, &line, stdin);
#else
		h = _getline(info, buf, &line);
#endif
		if (h > 0)
		{
			if ((*buf)[h - 1] == '\n')
			{
				(*buf)[h - 1] = '\0';
				h--;
			}
			info->linecount_flag = 1;
			remove_comments(*buf);
			build_history_list(info, *buf, info->histcount++);
			{
				*len = h;
				info->cmd_buf = buf;
			}
		}
	}
	return (h);
}

/**
 * get_input - gets a newline
 * @info: parameter struct
 * Return: bytes read
 */
ssize_t get_input(info_t *info)
{
	static char *buf;
	static size_t x;
	static size_t y;
	static size_t len;
	ssize_t h = 0;
	char **buf_p = &(info->arg);
	char *ptr;

	_putchar(BUF_FLUSH);
	h = input_buf(info, &buf, &len);
	if (h == -1)		 /* Ctrl+D */
		return (-1);
	if (len)
	{
		y = x;
		ptr = buf + x;

		check_chain(info, buf, &y, x, len);
		while (y < len)
		{
			if (is_chain(info, buf, &y))
				break;
			y++;
		}

		x = y + 1;
		if (x >= len)
		{
			x = len = 0;
			info->cmd_buf_type = CMD_NORM;
		}

		*buf_p = ptr;
		return (_strlen(ptr));
	}

	*buf_p = buf;
	return (h);
}

/**
 * read_buf - reads a buffer
 * @info: parameter struct
 * @buf: buffer
 * @size: size
 * Return: h
 */
ssize_t read_buf(info_t *info, char *buf, size_t *size)
{
	ssize_t h = 0;

	if (*size)
		return (0);
	h = read(info->readfd, buf, READ_BUF_SIZE);
	if (h >= 0)
		*size = h;
	return (h);
}

/**
 * _getline - gets the next line from input
 * @info: parameter struct
 * @ptr: address of pointer to buffer
 * @len: size of buffer
 * Return: size
 */
int _getline(info_t *info, char **ptr, size_t *len)
{
	static char buf[READ_BUF_SIZE];
	static size_t x;
	static size_t l;
	size_t k;
	ssize_t h = 0;
	ssize_t t = 0;
	char *p = NULL;
	char *pointer = NULL;
	char *c;
	
	p = *ptr;
	if (p && len)
		t = *len;
	if (x == l)
		x = l = 0;
	h = read_buf(info, buf, &l);
	if (h == -1 || (h == 0 && l == 0))
		return (-1);

	c = _strchr(buf + x, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : l;
	pointer = _realloc(p, t, t ? t + k : k + 1);
	if (!pointer)
		return (p ? free(p), -1 : -1);

	if (t)
		_strncat(pointer, buf + x, k - x);
	else
		_strncpy(pointer, buf + x, k - x + 1);

	t += k - x;
	x = k;
	p = pointer;

	if (len)
		*len = t;
	*ptr = p;
	return (t);
}

/**
 * sigintHandler - sigint handler of the shell
 * @num: the signal number
 * Return: void
 */
void sigintHandler(__attribute__((unused))int num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}
