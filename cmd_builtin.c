#include "shell.h"

/**
 * _myhistory - displays the history list
 * @info: Structure of the potential arguments
 *  Return: Always 0
 */
int _myhistory(info_t *info)
{
	print_list(info->history);
	return (0);
}

/**
 * unset_alias - sets the string alias
 * @info: parameter struct and info of the shell
 * @str: the string alias
 * Return: Always 0
 */
int unset_alias(info_t *info, char *str)
{
	char *ptr;
	char c;
	int x;

	ptr = _strchr(str, '=');
	if (!ptr)
		return (1);
	c = *ptr;
	*ptr = 0;
	x = delete_node_at_index(&(info->alias),
		get_node_index(info->alias, node_starts_with(info->alias, str, -1)));
	*ptr = c;
	return (x);
}

/**
 * set_alias - sets alias to string
 * @info: parameter struct and info
 * @str: the string alias
 * Return: Always 0 
 */
int set_alias(info_t *info, char *str)
{
	char *ptr;

	ptr = _strchr(str, '=');
	if (!ptr)
		return (1);
	if (!*++ptr)
		return (unset_alias(info, str));

	unset_alias(info, str);
	return (add_node_end(&(info->alias), str, 0) == NULL);
}

/**
 * print_alias - prints string alias
 * @node: the alias node
 * Return: Always 0
 */
int print_alias(list_t *node)
{
	char *ptr = NULL;
	char *h = NULL;

	if (node)
	{
		ptr = _strchr(node->str, '=');
		for (h = node->str; h <= ptr; h++)
			_putchar(*h);
		_putchar('\'');
		_puts(ptr + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * _myalias - mimics the alias builtin
 * @info: Structure of the potential arguments
 *  Return: Always 0
 */
int _myalias(info_t *info)
{
	int x = 0;
	char *ptr = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (x = 1; info->argv[x]; x++)
	{
		ptr = _strchr(info->argv[x], '=');
		if (ptr)
			set_alias(info, info->argv[x]);
		else
			print_alias(node_starts_with(info->alias, info->argv[x], '='));
	}

	return (0);
}
