#include "shell.h"

/**
 * bfree - frees a pointer
 * @p: address of the pointer
 * Return: 1 is freed or 0 is not
 */
int bfree(void **p)
{
	if (p && *p)
	{
		free(*p);
		*p = NULL;
		return (1);
	}
	return (0);
}
