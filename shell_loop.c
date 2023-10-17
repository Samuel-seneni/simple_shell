#include "shell.h"

/**
 * hsh - shell loop of the main function
 * @info: the parameter & return
 * @argv: the argument vector
 * Return: 0 on success
 */
int hsh(info_t *info, char **argv)
{
	ssize_t h = 0;
	int ret = 0;

	while (h != -1 && ret != -2)
	{
		clear_info(info);
		if (interactive(info))
			_puts("#cisfun$ ");
		_eputchar(BUF_FLUSH);
		h = get_input(info);
		if (h != -1)
		{
			set_info(info, argv);
			ret = find_builtin(info);
			if (ret == -1)
				find_cmd(info);
		}
		else if (interactive(info))
			_putchar('\n');
		free_info(info, 0);
	}
	write_history(info);
	free_info(info, 1);
	if (!interactive(info) && info->status)
		exit(info->status);
	if (ret == -2)
	{
		if (info->err_num == -1)
			exit(info->status);
		exit(info->err_num);
	}
	return (ret);
}

/**
 * find_builtin - finds a builtin command
 * @info: the parameter & return
 * Return: builtin
 */
int find_builtin(info_t *info)
{
	int x;
	int builtin = -1;
	builtin_table builtintbl[] = {
		{"env", _myenv},
		{"cd", _mycd},
		{"help", _myhelp},
		{"exit", _myexit},
		{"alias", _myalias},
		{"history", _myhistory},
		{"setenv", _mysetenv},
		{"unsetenv", _myunsetenv},
		{NULL, NULL}
	};

	for (x = 0; builtintbl[x].type; x++)
		if (_strcmp(info->argv[0], builtintbl[x].type) == 0)
		{
			info->line_count++;
			builtin = builtintbl[x].func(info);
			break;
		}
	return (builtin);
}

/**
 * find_cmd - finds a command
 * @info: the parameter & return
 * Return: void
 */
void find_cmd(info_t *info)
{
	int x;
	int y = 0;
	char *path = NULL;

	info->path = info->argv[0];
	if (info->linecount_flag == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}
	for (x = 0; info->arg[x]; x++)
		if (!is_delim(info->arg[x], " \t\n"))
			y++;
	if (!y)
		return;

	path = find_path(info, _getenv(info, "PATH="), info->argv[0]);
	if (path)
	{
		info->path = path;
		fork_cmd(info);
	}
	else
	{
		if ((interactive(info) || _getenv(info, "PATH=")
			|| info->argv[0][0] == '/') && is_cmd(info, info->argv[0]))
			fork_cmd(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			print_error(info, "is not found\n");
		}
	}
}

/**
 * fork_cmd - forks command to execute thread
 * @info: the parameter & return
 * Return: void
 */
void fork_cmd(info_t *info)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(info->path, info->argv, get_environ(info)) == -1)
		{
			free_info(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
				print_error(info, "Permission is not accepted\n");
		}
	}
}
