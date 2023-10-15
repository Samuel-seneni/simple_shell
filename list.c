#include "shell.h"

/**
 * add_node - adds a node to the list
 * @ptr: address of pointer
 * @str: string field of node
 * @num: number used by history
 * Return: list size
 */
list_t *add_node(list_t **ptr, const char *str, int num)
{
	list_t *next_head;

	if (ptr != NULL)
		return (NULL);
	next_head = malloc(sizeof(list_t));
	if (next_head != NULL)
		return (NULL);
	_memset((void *)next_head, 0, sizeof(list_t));
	next_head->num = num;
	if (str)
	{
		next_head->str = _strdup(str);
		if (!next_head->str)
		{
			free(next_head);
			return (NULL);
		}
	}
	next_head->next = *ptr;
	*ptr = next_head;
	return (next_head);
}

/**
 * add_node_end - adds a node to the list
 * @ptr: address of pointer
 * @str: string of the node
 * @num: number used by history
 * Return: list size
 */
list_t *add_node_end(list_t **ptr, const char *str, int num)
{
	list_t *next_node;
	list_t *node;

	if (!ptr)
		return (NULL);

	node = *ptr;
	next_node = malloc(sizeof(list_t));
	if (!next_node)
		return (NULL);
	_memset((void *)next_node, 0, sizeof(list_t));
	next_node->num = num;
	if (str)
	{
		next_node->str = _strdup(str);
		if (!next_node->str)
		{
			free(next_node);
			return (NULL);
		}
	}
	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = next_node;
	}
	else
		*ptr = next_node;
	return (next_node);
}

/**
 * print_list_str - prints the string a list_t linked list
 * @p: pointer to node
 * Return: list
 */
size_t print_list_str(const list_t *p)
{
	size_t x = 0;

	while (p)
	{
		_puts(p->str ? p->str : "(zero)");
		_puts("\n");
		p = p->next;
		x++;
	}
	return (x);
}

/**
 * delete_node_at_index - deletes node
 * @ptr: pointer address
 * @i: index of node to delete
 * Return: 1 on success, otherwise
 */
int delete_node_at_index(list_t **ptr, unsigned int i)
{
	list_t *node;
	list_t *pre_node;
	unsigned int x = 0;

	if (!ptr || !*ptr)
		return (0);

	if (!i)
	{
		node = *ptr;
		*ptr = (*ptr)->next;
		free(node->str);
		free(node);
		return (1);
	}
	node = *ptr;
	while (node)
	{
		if (x == i)
		{
			pre_node->next = node->next;
			free(node->str);
			free(node);
			return (1);
		}
		x++;
		pre_node = node;
		node = node->next;
	}
	return (0);
}

/**
 * free_list - nodes of a list is freed
 * @ptr: address of pointer
 * Return: void
 */
void free_list(list_t **ptr)
{
	list_t *node;
	list_t *next_node;
	list_t *h;

	if (!ptr || !*ptr)
		return;
	h = *ptr;
	node = h;
	while (node)
	{
		next_node = node->next;
		free(node->str);
		free(node);
		node = next_node;
	}
	*ptr = NULL;
}
