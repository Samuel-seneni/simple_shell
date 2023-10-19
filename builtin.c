#include "shell.h"

/**
 * _myexit - exits the shell
 * @info: Structure of the  potential arguments
 *  Return: exit status
 */
int _myexit(info_t *info)
{
	int exit;

	if (info->argv[1])
	{
		exit = _erratoi(info->argv[1]);
		if (exit == -1)
		{
			info->status = 2;
			print_error(info, "error number: ");
			_eputs(info->argv[1]);
			_eputchar('\n');
			return (1);
		}
		info->err_num = _erratoi(info->argv[1]);
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}

/**
 * _mycd - changes the current directory of the process
 * @info: Structure of the potential arguments
 *  Return: Always 0
 */
int _mycd(info_t *info)
{
	char *p;
	char *d;
	char buffer[1024];
	int x;

	p = getcwd(buffer, 1024);
	if (!p)
		_puts("TODO: >>getcwd msg error here<<\n");
	if (!info->argv[1])
	{
		d = _getenv(info, "HOME=");
		if (!d)

			x = chdir((d = _getenv(info, "PWD=")) ? d : "/");
		else
			x = chdir(d);
	}
	else if (_strcmp(info->argv[1], "-") == 0)
	{
		if (!_getenv(info, "EXPWD="))
		{
			_puts(p);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(info, "EXPWD=")), _putchar('\n');
		x = chdir((d = _getenv(info, "EXPWD=")) ? d : "/");
	}
	else
		x = chdir(info->argv[1]);
	if (x == -1)
	{
		print_error(info, "can not cd to ");
		_eputs(info->argv[1]), _eputchar('\n');
	}
	else
	{
		_setenv(info, "EXPWD", _getenv(info, "PWD="));
		_setenv(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * _myhelp - the current directory of the process
 * @info: Structure of the potential arguments
 * Return: Always 0
 */
int _myhelp(info_t *info)
{
	char **arga;

	arga = info->argv;
	_puts("Function is no implemented \n");
	if (0)
		_puts(*arga);
	return (0);
}
