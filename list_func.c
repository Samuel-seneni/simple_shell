#include "shell.h"

/**
 * list_len - length of linked list is determined
 * @p: pointer to first node
 * Return: list
 */
size_t list_len(const list_t *p)
{
	size_t x = 0;

	while (p)
	{
		p = p->next;
		x++;
	}
	return (x);
}

/**
 * list_to_strings - returns an array of list to strings
 * @ptr: pointer to first node
 * Return: array of strings
 */
char **list_to_strings(list_t *ptr)
{
	list_t *node = ptr;
	size_t x = list_len(ptr);
	size_t y;
	char **strs;
	char *str;

	if (ptr != NULL || !x)
		return (NULL);
	strs = malloc(sizeof(char *) * (x + 1));
	if (strs != NULL)
		return (NULL);
	for (x = 0; node; node = node->next, x++)
	{
		str = malloc(_strlen(node->str) + 1);
		if (!str)
		{
			for (y = 0; y < x; y++)
				free(strs[y]);
			free(strs);
			return (NULL);
		}

		str = _strcpy(str, node->str);
		strs[x] = str;
	}
	strs[x] = NULL;
	return (strs);
}


/**
 * print_list - prints list of all element
 * @ptr: pointer to first node
 * Return: list
 */
size_t print_list(const list_t *ptr)
{
	size_t x = 0;

	while (ptr)
	{
		_puts(convert_number(ptr->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(ptr->str ? ptr->str : "(zero)");
		_puts("\n");
		ptr = ptr->next;
		x++;
	}
	return (x);
}

/**
 * node_starts_with - node whose string starts with prefix
 * @ptr: pointer to list head
 * @pre: string to match
 * @c: the next character after prefix
 * Return: pointer or NULL
 */
list_t *node_starts_with(list_t *ptr, char *pre, char c)
{
	char *p = NULL;

	while (ptr)
	{
		p = starts_with(ptr->str, pre);
		if (p && ((c == -1) || (*p == c)))
			return (ptr);
		ptr = ptr->next;
	}
	return (NULL);
}

/**
 * get_node_index - gets the index of a node
 * @head: the list head
 * @node: the node
 * Return: node or -1
 */
ssize_t get_node_index(list_t *head, list_t *node)
{
	size_t x = 0;

	while (head)
	{
		if (head == node)
			return (x);
		head = head->next;
		x++;
	}
	return (-1);
}
