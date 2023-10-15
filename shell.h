#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;


/**
 * struct liststr - singly linked list
 * @num: the number
 * @str: a string
 * @next: next node
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

typedef struct passinfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;
	char **cmd_buf;
	int cmd_buf_type;
	int readfd;
	int histcount;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
 *struct builtin - builtin structure of the shell
 *@type: the builtin type
 *@func: the function
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;

int hsh(info_t *info, char **argv);
int find_builtin(info_t *info);
void find_cmd(info_t *info);
void fork_cmd(info_t *info);
int is_cmd(info_t *info, char *path);
char *dup_chars(char *path, int start, int stop);
char *find_path(info_t *info, char *str, char *cmd);
int interactive(info_t *info);
int is_delim(char c, char *delim);
int _isalpha(int c);
int _atoi(char *str);
int _myexit(info_t *info);
int _mycd(info_t *info);
int _myhelp(info_t *info);
int _myhistory(info_t *info);
int unset_alias(info_t *info, char *str);
int set_alias(info_t *info, char *str);
int print_alias(list_t *n);
int _myalias(info_t *info);
int _myenv(info_t *info);
char *_getenv(info_t *info, const char *str);
int _mysetenv(info_t *info);
int _myunsetenv(info_t *info);
int populate_env_list(info_t *info);
void _eputs(char *str);
int _eputchar(char c);
int _putfd(char c, int fd);
int _putsfd(char *str, int fd);
int _erratoi(char *str);
void print_error(info_t *info, char *strerr);
int print_d(int input, int fd);
char *convert_number(long int num, int base, int flags);
void remove_comments(char *buf);
char *_strncpy(char *dest, char *src, int h);
char *_strncat(char *s1, char *s2, int h);
char *_strchr(char *str, char c);
char **get_environ(info_t *info);
int _unsetenv(info_t *info, char *var);
int _setenv(info_t *info, char *var, char *val);
void clear_info(info_t *info);
void set_info(info_t *info, char **av);
void free_info(info_t *info, int fld);
ssize_t input_buf(info_t *info, char **buf, size_t *len);
ssize_t get_input(info_t *info);
ssize_t read_buf(info_t *info, char *buf, size_t *size);
int _getline(info_t *info, char **ptr, size_t *len);
void sigintHandler(__attribute__((unused))int num);
int bfree(void **p);
char *_memset(char *ptr, char bytes, unsigned int n);
void ffree(char **str);
void *_realloc(void *ptr, unsigned int old, unsigned int new);
int main(int argc, char **argv);
int hsh(info_t *info, char **argv);
int find_builtin(info_t *info);
void find_cmd(info_t *info);
void fork_cmd(info_t *info);
int _strlen(char *str);
int _strcmp(char *str1, char *str2);
char *starts_with(const char *haystack, const char *string);
char *_strcat(char *dest, char *src);
char *_strcpy(char *dest, char *src);
char *_strdup(const char *str);
void _puts(char *str);
int _putchar(char c);
char **strtow(char *str, char *delim);
char **strtow2(char *str, char delim);
char *get_history_file(info_t *info);
int write_history(info_t *info);
int read_history(info_t *info);
int build_history_list(info_t *info, char *buf, int count);
int renumber_history(info_t *info);
list_t *add_node(list_t **ptr, const char *str, int num);
list_t *add_node_end(list_t **ptr, const char *str, int num);
size_t print_list_str(const list_t *p);
int delete_node_at_index(list_t **ptr, unsigned int i);
void free_list(list_t **ptr);
size_t list_len(const list_t *p);
char **list_to_strings(list_t *ptr);
size_t print_list(const list_t *ptr);
list_t *node_starts_with(list_t *ptr, char *pre, char c);
ssize_t get_node_index(list_t *head, list_t *node);
int is_chain(info_t *info, char *buf, size_t *pos);
void check_chain(info_t *info, char *buf, size_t *p, size_t start, size_t len);
int replace_alias(info_t *info);
int replace_vars(info_t *info);
int replace_string(char **prev, char *cur);

#endif
