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


#define RBS 1024
#define WBS 1024
#define BFL -1


#define CNRM    0
#define CMDO            1
#define CMD_AND         2
#define CMD_CHAIN       3


#define CONVERT_LOWERCASE       1
#define CONVERT_UNSIGNED        2


#define USE_GETLINE 0
#define USE_STRTOK 0

#define HISTFLE ".simple_shell_hist"
#define HMAX    4096

extern char **environ;


/**
 * size_truct liststr - single list
 * @num: field number
 * @str: size_tr
 * @next: next nde pointer
 */
typedef size_truct liststr
{
	int num;
	char *str;
	struct liststr *next;
} lt;

/**
 * size_truct passinf - has pseudo args
 * @arg: args from getline
 * @argv: args vecto
 * @pth: a size_tr pth of current command
 * @argc: the arg counter
 * @linco: the error counter
 * @errn: the error code for exit()s
 * @linecofg: count uses this input line
 * @fname: the program fnme
 * @env: copy of env
 * @environ: mlodified copy of env
 * @hist: the hisize_t nde
 * @alias: the alias nde
 * @changed_env: shows change of environment
 * @sts: the return size_ts executable command
 * @cbuf: cbuf pointer address
 * @cbt: CMD_type ||, &&, ;
 * @rfd: reading of line of input begins
 * @hcnt: the hisize_t line counter
 */
typedef size_truct passinf
{
	char *arg;
	char **argv;
	char *pth;
	int argc;
	unsigned int linco;
	int errn;
	int linecofg;
	char *fname;
	lt *env;
	lt *hist;
	lt *alias;
	char **environ;
	int changed_env;
	int size_ts;

	char **cbuf;
	int cbt;
	int rfd;
	int hcnt;
} inf_t;

#define INITINF \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
				0, 0, 0}

/**
 * size_truct blin - contains a blin size_tring and related function
 * @type: the blin command fg
 * @func: the function
 */
typedef size_truct blin
{
	char *type;
	int (*func)(inf_t *);
} blin_table;
int hsh(inf_t *, char **);
int find_blin(inf_t *);
void fcmd(inf_t *);
void forkcd(inf_t *);


int icmd(inf_t *, char *);
char *chardup(char *, int, int);
char *fpth(inf_t *, char *, char *);
int loophsh(char **);
void _eps(char *);
int _epc(char);
int _ptfd(char c, int fd);
int _psfd(char *str, int fd);

int _strlen(char *);
int _strcmp(char *, char *);
char *sw(const char *, const char *);
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
void ffr(char **);
void *_realloc(void *, unsigned int, unsigned int);

int bfree(void **);

int interactive(inf_t *);
int is_delim(char, char *);
int _ipa(int);
int _stoi(char *);

int _errstoi(char *);
void printer(inf_t *, char *);
int print_d(int, int);
char *convertnum(long int, int, int);
void rmcomments(char *);

int _mxt(inf_t *);
int _md(inf_t *);
int _myhp(inf_t *);

int _myhist(inf_t *);
int _myal(inf_t *);

ssize_t get_in(inf_t *);
int _getline(inf_t *, char **, size_t *);
void sgtHandler(int);

void clif(inf_t *);
void setin(inf_t *, char **);
void frinf(inf_t *, int);

char *gev(inf_t *, const char *);
int _myv(inf_t *);
int _mysev(inf_t *);
int _myunsev(inf_t *);
int popenvl(inf_t *);

char **get_environ(inf_t *);
int _unsev(inf_t *, char *);
int _sev(inf_t *, char *, char *);
char *ghf(inf_t *inf);
int write_hist(inf_t *inf);
int rdhist(inf_t *inf);
int bhl(inf_t *inf, char *buf, int lcnt);
int renum_hist(inf_t *inf);

lt *add_nde(lt **, const char *, int);
lt *add_end(lt **, const char *, int);
size_t plstr(const lt *);
int del_ind(lt **, unsigned int);
void free_l(lt **);

size_t llen(const lt *);
char **lst(lt *);
size_t print_lst(const lt *);
lt *st_nde(lt *, char *, char);
ssize_t get_ind(lt *, lt *);

int ichain(inf_t *, char *, size_t *);
void chchain(inf_t *, char *, size_t *, size_t, size_t);
int repalias(inf_t *);
int repvrs(inf_t *);
int r_str(char **, char *);
#endif
