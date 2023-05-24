#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <signal.h>
#include <limits.h>

/* DEFINED CONSTANT MACROS */
#define BUFSIZE 256
#define ENOSTRING 1106
#define EILLEGAL 227
#define EWSIZE 410
#define ENOBUILTIN 415
#define EBADCD 726

extern char **environ;

/**
 * struct linlist - data structure for linked list
 * @str: string path name
 * @nxt: pointer to next node in the list
 */
typedef struct linlist
{
	char *str;
	struct linlist *nxt;
} lin_t;

/**
 * struct variables - contains values for structure
 * @enviroment: local enviroment variables in linked list
 * @enviromentList: array of enviroment variables strings
 * @args: arguments strings
 * @buffer: temporary buffer for user input
 * @path: path variable
 * @fpath: path with prepended path variable
 * @shellName: the name of the shell
 * @count: number of lines entered
 * @error: child process error status
 */
typedef struct variables
{
	lin_t *enviroment;
	char **enviromentList;
	char **args;
	char *buffer;
	char *path;
	char *fpath;
	char *shellName;
	unsigned int count;
	int error;
} vars_t;

/**
 * struct inborns - the shell and associated functions
 * @cmd: input cmd
 * @func: output function
 */
typedef struct inborns
{
	char *cmd;
	int (*func)(vars_t *build);
} inborns_t;


vars_t *vars_tInit(vars_t *build);


bool findinborns(vars_t *build);
int exitFunc(vars_t *build);


int cdFunc(vars_t *);
bool cdToHome(vars_t *build);
bool cdToPrevious(vars_t *build);
bool cdToCustom(vars_t *build);
bool updEnviron(vars_t *build);


int updold(vars_t *build);
bool updcur(vars_t *build, int index);

/* environment */
int envFunc(vars_t *build);
int setenvFunc(vars_t *build);
int unsetenvFunc(vars_t *build);
int _isalpha(int c);

/* help functions*/
int helpFunc(vars_t *build);
int helpmenu(void);
int helpExit(vars_t *build);
int helpEnv(vars_t *build);


/* more help functions */

int cd_help(vars_t *biuld);
int helpSetenv(vars_t *build);
int helpUnsetenv(vars_t *build);
int helpHelp(vars_t *build);

/* inbuilt help functions*/
int countArgs(char **args);
int _atoi(char *s);


void shell(vars_t *build);
void get_line(vars_t *build);
void forkAndExecute(vars_t *build);
void stripComments(char *str);
void convertLLtoArr(vars_t *build);

/* get environment path variable */
char *_getenv(char *input, char **environ);

/* error handling function */
void errorHandler(vars_t *build);
unsigned int countDigits(int num);
char *itoa(unsigned int num);
char *getErrorMessage();

/* shell support functions */
void insert_null_byte(char *s, unsigned int index);
void displayPrompt(void);
void displayNewLine(void);
void sigintHandler(int sigint);

/* get and check path */
bool checkPath(vars_t *);
bool checkEdgeCases(vars_t *build);


bool splitString(vars_t *build);
unsigned int countWords(char *s);
bool isSpace(char c);


int _strlen(char *s);
char *_strcat(char *dest, char *src);
int _strcmp(char *s1, char *s2);
char *_strdup(char *str);
char *_strcpy(char *dest, char *src);


char *_strtok(char *str, char *delim);
int _strcspn(char *string, char *chars);
char *_strchr(char *s, char c);


lin_t *addNode(lin_t **head, char *str);
lin_t *addNodeEnd(lin_t **head, char *str);
size_t printList(const lin_t *h);
int searchNode(lin_t *head, char *str);
size_t list_len(lin_t *h);


int deleteNodeAtIndex(lin_t **head, unsigned int index);
lin_t *generateLinkedList(char **array);
lin_t *addNodeAtIndex(lin_t **head, int index, char *str);
char *getNodeAtIndex(lin_t *head, unsigned int index);

/* memory alloc and realloc */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
char *_memcpy(char *dest, char *src, unsigned int n);

/* free allocated memories */
void freeMembers(vars_t *build);
void freeArgsAndBuffer(vars_t *build);
void freeArgs(char **args);
void freeList(lin_t *head);

#endif /* SHELL_H */
