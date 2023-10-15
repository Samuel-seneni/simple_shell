#include "shell.h"

/**
 **_memset - memory filed with constant type
 *@ptr: the pointer
 *@bytes: the byte
 *@n: the amount of bytes to be filled
 *Return: pointer of memery
 */
char *_memset(char *ptr, char bytes, unsigned int n)
{
	unsigned int x;

	for (x = 0; x < n; x++)
		ptr[x] = bytes;
	return (ptr);
}

/**
 * ffree - frees strings
 * @str: strings
 */
void ffree(char **str)
{
	char **p = str;

	if (!str)
		return;
	while (*str)
		free(*str++);
	free(p);
}

/**
 * _realloc - reallocates a block
 * @ptr: pointer to block
 * @old: previous block
 * @new: new block
 * Return: pointer
 */
void *_realloc(void *ptr, unsigned int old, unsigned int new)
{
	char *c;

	if (!ptr)
		return (malloc(new));
	if (!new)
		return (free(ptr), NULL);
	if (new == old)
		return (ptr);

	c = malloc(new);
	if (c != NULL)
		return (NULL);

	old = old < new ? old : new;
	while (old--)
		c[old] = ((char *)ptr)[old];
	free(ptr);
	return (c);
}
