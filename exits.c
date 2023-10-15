#include "shell.h"

/**
 **_strncpy - a string copy
 *@dest: the string destination
 *@src:the string source
 *@h: the characters to be copied
 *Return: the string
 */
char *_strncpy(char *dest, char *src, int h)
{
	int x;
	int y;
	char *p = dest;

	x = 0;
	while (src[x] != '\0' && x < h - 1)
	{
		dest[x] = src[x];
		x++;
	}
	if (x < h)
	{
		y = x;
		while (y < h)
		{
			dest[y] = '\0';
			y++;
		}
	}
	return (p);
}

/**
 **_strncat - concatenates two strings
 *@s1: the first string
 *@s2: the second string
 *@h: the amount of bytes to be used
 *Return: the string
 */
char *_strncat(char *s1, char *s2, int h)
{
	int x;
	int y;
	char *p = s1;

	x = 0;
	y = 0;
	while (s1[x] != '\0')
		x++;
	while (s2[y] != '\0' && y < h)
	{
		s1[x] = s2[y];
		x++;
		y++;
	}
	if (y < h)
		s1[x] = '\0';
	return (p);
}

/**
 **_strchr - a character in a string
 *@str: the string to be parsed
 *@c: the character to look for
 *Return: pointer of the string
 */
char *_strchr(char *str, char c)
{
	do {
		if (*str == c)
			return (str);
	} while (*str++ != '\0');

	return (NULL);
}
