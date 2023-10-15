#include "shell.h"

/**
 * _strlen - returns the string length
 * @str: the string
 * Return: integer
 */
int _strlen(char *str)
{
	int x = 0;

	if (!str)
		return (0);

	while (*str++)
		x++;
	return (x);
}

/**
 * _strcmp - performs comparison of the string
 * @str1: the first string
 * @str2: the second string
 * Return: string
 */
int _strcmp(char *str1, char *str2)
{
	while (*str1 && *str2)
	{
		if (*str1 != *str2)
			return (*str1 - *str2);
		str1++;
		str2++;
	}
	if (*str1 == *str2)
		return (0);
	else
		return (*str1 < *str2 ? -1 : 1);
}

/**
 * starts_with - needle starts with haystack is checked
 * @haystack: searched string
 * @string: the string to find
 * Return: address of haystack or NULL
 */
char *starts_with(const char *haystack, const char *string)
{
	while (*string)
		if (*string++ != *haystack++)
			return (NULL);
	return ((char *)haystack);
}

/**
 * _strcat - concatenates two strings
 * @dest: the destination buffer of the string
 * @src: the source buffer of the string
 * Return: destination
 */
char *_strcat(char *dest, char *src)
{
	char *r = dest;

	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = *src;
	return (r);
}
