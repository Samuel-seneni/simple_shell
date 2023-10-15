#include "shell.h"

/**
 * _erratoi - string to be converted to integer
 * @str: the string
 * Return: 0
 */
int _erratoi(char *str)
{
	int x = 0;
	unsigned long int res = 0;

	if (*str == '+')
		str++;
	for (x = 0;  str[x] != '\0'; x++)
	{
		if (str[x] >= '0' && str[x] <= '9')
		{
			res *= 10;
			res += (str[x] - '0');
			if (res > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (res);
}

/**
 * print_error - prints an error
 * @info: the parameter & return of address
 * @strerr: string error type
 * Return: 0
 */
void print_error(info_t *info, char *strerr)
{
	_eputs(info->fname);
	_eputs(": ");
	print_d(info->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(info->argv[0]);
	_eputs(": ");
	_eputs(strerr);
}

/**
 * print_d - convert decimal number to integer
 * @input: the input
 * @fd: the filedescripto
 * Return: the character
 */
int print_d(int input, int fd)
{
	int (*__putchar)(char) = _putchar;
	int x;
	int count = 0;
	unsigned int b;
	unsigned int c;

	if (fd == STDERR_FILENO)
		__putchar = _eputchar;
	if (input < 0)
	{
		b = -input;
		__putchar('-');
		count++;
	}
	else
		c = input;
	c = b;
	for (x = 1000000000; x > 1; x /= 10)
	{
		if (b / x)
		{
			__putchar('0' + c / x);
			count++;
		}
		c %= x;
	}
	__putchar('0' + c);
	count++;

	return (count);
}

/**
 * convert_number - converter a number
 * @num: number
 * @base: base
 * @flags: flags
 * Return: string
 */
char *convert_number(long int num, int base, int flags)
{
	static char *r;
	static char buffer[50];
	char s = 0;
	char *ptr;
	unsigned long h = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		h = -num;
		s = '-';

	}
	r = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do	{
		*--ptr = r[h % base];
		h /= base;
	} while (h != 0);

	if (s)
		*--ptr = s;
	return (ptr);
}

/**
 * remove_comments - remove the comments
 * @buf: address of the buffer
 * Return: Always 0;
 */
void remove_comments(char *buf)
{
	int x;

	for (x = 0; buf[x] != '\0'; x++)
		if (buf[x] == '#' && (!x || buf[x - 1] == ' '))
		{
			buf[x] = '\0';
			break;
		}
}
