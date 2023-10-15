#include "shell.h"

/**
 * interactive - interactive mode of the shell
 * @info: struct address of the shell
 * Return: interactive mode
 */
int interactive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * is_delim - checks a delimeter of the character
 * @c: to check the char
 * @delim: the delimeter
 * Return: 1 if true, 0 otherwise
 */
int is_delim(char c, char *delim)
{
	while (*delim)
		if (*delim++ == c)
			return (1);
	return (0);
}

/**
 *_isalpha - alphabetic character to be checked
 *@c: The character of the shell to input
 *Return: 1 if true otherwise 0
 */

int _isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 *_atoi - a string converted into an integer
 *@str: the string of the shell converted
 *Return: 0
 */

int _atoi(char *str)
{
	int x;
	int s = 1;
	int f = 0;
	int output;
	unsigned int res = 0;

	for (x = 0;  str[x] != '\0' && f != 2; x++)
	{
		if (str[x] == '-')
			s *= -1;

		if (str[x] >= '0' && str[x] <= '9')
		{
			f = 1;
			res *= 10;
			res += (str[x] - '0');
		}
		else if (f == 1)
			f = 2;
	}

	if (s == -1)
		output = -res;
	else
		output = res;

	return (output);
}
