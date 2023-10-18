#include "shell.h"

/**
 * **strtow - splits a string into word
 * @str: the string
 * @delim: the delimeter
 * Return: a pointer
 */

char **strtow(char *str, char *delim)
{
	char **ptr;
	int x;
	int y;
	int k;
	int m;
	int num = 0;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!delim)
		delim = " ";
	for (x = 0; str[x] != '\0'; x++)
	if (!is_delim(str[x], delim) && (is_delim(str[x + 1], delim)
			|| !str[x + 1])) num++;

	if (num == 0)
		return (NULL);
	ptr = malloc((1 + num) * sizeof(char *));
	if (!ptr)
		return (NULL);
	for (x = 0, y = 0; y < num; y++)
	{
		while (is_delim(str[x], delim))
			x++;
		k = 0;
		while (!is_delim(str[x + k], delim) && str[x + k])
			k++;
		ptr[y] = malloc((k + 1) * sizeof(char));
		if (!ptr[y])
		{
			for (k = 0; k < y; k++)
				free(ptr[k]);
			free(ptr);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			ptr[y][m] = str[x++];
		ptr[y][m] = 0;
	}
	ptr[y] = NULL;
	return (ptr);
}

/**
 * **strtow2 - splits a string into words
 * @str: the string
 * @delim: the delimeter
 * Return: a pointer
 */
char **strtow2(char *str, char delim)
{
	int x;
	int y;
	int k;
	int m;
	int num = 0;
	char **ptr;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (x = 0; str[x] != '\0'; x++)
		if ((str[x] != delim && str[x + 1] == delim) ||
		    (str[x] != delim && !str[x + 1]) || str[x + 1] == delim)
			num++;
	if (num == 0)
		return (NULL);
	ptr = malloc((1 + num) * sizeof(char *));
	if (!ptr)
		return (NULL);
	for (x = 0, y = 0; y < num; y++)
	{
		while (str[x] == delim && str[x] != delim)
			x++;
		k = 0;
		while (str[x + k] != delim && str[x + k] && str[x + k] != delim)
			k++;
		ptr[y] = malloc((k + 1) * sizeof(char));
		if (!ptr[y])
		{
			for (k = 0; k < y; k++)
				free(ptr[k]);
			free(ptr);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			ptr[y][m] = str[x++];
		ptr[y][m] = 0;
	}
	ptr[y] = NULL;
	return (ptr);
}
