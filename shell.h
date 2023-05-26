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


#define USE_gtLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;


/**
 * struct liststr - singly lkd lst
 * @num: the numb fild
 * @str: a strg
 * @next: pnts to the next nde
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 * struct passinfo - conts pseudo-arguements to pass into a fnct,
 * allowing uniform prototype for fnct pntr struct
 * @arg: a strg generated from getline containing arguements
 * @argv:an array of strgs generated from arg
 * @path: a strg path for the curr command
 * @argc: the argmnt count
 * @line_count: the error count
 * @err_num: the error code for exit()s
 * @linecount_flag: if on count this line of input
 * @fname: the program filename
 * @env: lkd lst local copy of environ
 * @environ: custom modified copy of environ from LL env
 * @history: the history nde
 * @alias: the alias nde
 * @env_changed: on if environ was changed
 * @status: the return status of the last exec'd command
 * @cmd_buf: add of pntr to cmd_buf, on if chaining
 * @cmd_buf_type: CMD_type ||, &&, ;
 * @readfd: the fd from which to read line input
 * @histcount: the history line numb count
 */
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

	char **cmd_buf; /* pntr to cmd ; chain bf, for memory mangement */
	int cmd_buf_type; /* CMD_type ||, &&, ; */
	int readfd;
	int histcount;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
		0, 0, 0}

/**
 * struct bltin - conts a bltin strg and related fnct
 * @type: the bltin command flag
 * @func: the fnct
 */
typedef struct bltin
{
	char *type;
	int (*func)(info_t *);
} bltin_table;

int hsh(info_t *, char **);
int find_bltin(info_t *);
void find_cmd(info_t *);
void fork_cmd(info_t *);

int is_cmd(info_t *, char *);
char *dup_chars(char *, int, int);
char *find_path(info_t *, char *, char *);

int loophsh(char **);

void _eputs(char *);
int _eputchar(char);
int _putfd(char c, int fd);
int _putsfd(char *str, int fd);


int _strlen(char *);
int _strcmp(char *, char *);
char *starts_with(const char *, const char *);
char *_strcat(char *, char *);

char *_strcpy(char *, char *);
char *_strdup(const char *);
void _puts(char *);
int _putchar(char);


char *_strncpy(char *, char *, int);
char *_strncat(char *, char *, int);
char *_strchr(char *, char);

char **strtow(char *, char *);
char **strtow2(char *, char);

char *_memset(char *, char, unsigned int);
void ffree(char **);
void *_realloc(void *, unsigned int, unsigned int);

int bfree(void **);

int interactive(info_t *);
int is_delim(char, char *);
int _isalpha(int);
int _atoi(char *);

int _erratoi(char *);
void print_error(info_t *, char *);
int print_d(int, int);
char *convert_number(long int, int, int);
void remove_comments(char *);

int _ourexit(info_t *);
int _ourcd(info_t *);
int _ourhelp(info_t *);

int _ourhistory(info_t *);
int _ouralias(info_t *);

ssize_t get_input(info_t *);
int _gtline(info_t *, char **, size_t *);
void sigintHandler(int);

void clear_info(info_t *);
void set_info(info_t *, char **);
void free_info(info_t *, int);

char *_gtenv(info_t *, const char *);
int _ourenv(info_t *);
int _oursetenv(info_t *);
int _ourunsetenv(info_t *);
int populate_env_list(info_t *);

char **get_environ(info_t *);
int _unsetenv(info_t *, char *);
int _setenv(info_t *, char *, char *);

char *get_history_file(info_t *information);
int write_history(info_t *information);
int read_history(info_t *information);
int build_history_list(info_t *information, char *buff, int linecount);
int renumber_history(info_t *information);

list_t *add_nde(list_t **, const char *, int);
list_t *add_nde_end(list_t **, const char *, int);
size_t print_list_str(const list_t *);
int delete_nde_at_ind(list_t **, unsigned int);
void free_list(list_t **);

size_t list_len(const list_t *);
char **list_tostrs(list_t *);
size_t print_list(const list_t *);
list_t *nde_starts_with(list_t *, char *, char);
ssize_t get_nde_ind(list_t *, list_t *);

int is_chain(info_t *, char *, size_t *);
void check_chain(info_t *, char *, size_t *, size_t, size_t);
int replace_alias(info_t *);
int replace_vars(info_t *);
int replacestr(char **, char *);

#endif
