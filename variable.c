#include "shell.h"

/**
 * is_chain - test char in buffer if is a chain delimeter
 * @info: the parameter struct
 * @buf: the buffer
 * @pos: address of position in a buffer
 * Return: delimeter
 */
int is_chain(info_t *info, char *buf, size_t *pos)
{
	size_t y = *pos;

	if (buf[y] == '|' && buf[y + 1] == '|')
	{
		buf[y] = 0;
		y++;
		info->cmd_buf_type = CMD_OR;
	}
	else if (buf[y] == '&' && buf[y + 1] == '&')
	{
		buf[y] = 0;
		y++;
		info->cmd_buf_type = CMD_AND;
	}
	else if (buf[y] == ';')
	{
		buf[y] = 0;
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*pos = y;
	return (1);
}

/**
 * check_chain - checks chain of the last status
 * @info: the parameter struct
 * @buf: the char buffer
 * @p: address of current position
 * @start: starting position
 * @len: length
 * Return: Void
 */
void check_chain(info_t *info, char *buf, size_t *p, size_t start, size_t len)
{
	size_t y = *p;

	if (info->cmd_buf_type == CMD_AND)
	{
		if (info->status)
		{
			buf[start] = 0;
			y = len;
		}
	}
	if (info->cmd_buf_type == CMD_OR)
	{
		if (!info->status)
		{
			buf[start] = 0;
			y = len;
		}
	}

	*p = y;
}

/**
 * replace_alias - replaces an aliases in the tokenized string
 * @info: the parameter struct
 * Return: 1
 */
int replace_alias(info_t *info)
{
	int x;
	list_t *node;
	char *ptr;

	for (x = 0; x < 10; x++)
	{
		node = node_starts_with(info->alias, info->argv[0], '=');
		if (!node)
			return (0);
		free(info->argv[0]);
		ptr = _strchr(node->str, '=');
		if (!ptr)
			return (0);
		ptr = _strdup(ptr + 1);
		if (!ptr)
			return (0);
		info->argv[0] = ptr;
	}
	return (1);
}

/**
 * replace_vars - replaces vars in the tokenized
 * @info: the parameter struct
 * Return: 1
 */
int replace_vars(info_t *info)
{
	int x = 0;
	list_t *node;

	for (x = 0; info->argv[x]; x++)
	{
		if (info->argv[x][0] != '$' || !info->argv[x][1])
			continue;

		if (!_strcmp(info->argv[x], "$?"))
		{
			replace_string(&(info->argv[x]),
				_strdup(convert_number(info->status, 10, 0)));
			continue;
		}
		if (!_strcmp(info->argv[x], "$$"))
		{
			replace_string(&(info->argv[x]),
				_strdup(convert_number(getpid(), 10, 0)));
			continue;
		}
		node = node_starts_with(info->env, &info->argv[x][1], '=');
		if (node)
		{
			replace_string(&(info->argv[x]),
				_strdup(_strchr(node->str, '=') + 1));
			continue;
		}
		replace_string(&info->argv[x], _strdup(""));

	}
	return (0);
}

/**
 * replace_string - replaces string
 * @prev: previous string
 * @cur: current string
 * Return: 1
 */
int replace_string(char **prev, char *cur)
{
	free(*prev);
	*prev = cur;
	return (1);
}
