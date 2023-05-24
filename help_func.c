#include "shell.h"

/**
 * helpFunc - fetch instructions on usage of built in commands
 *
 * @build: input build
 *
 * Return: Always 1
 */
int helpFunc(vars_t *build)
{
	inborns_t help_arr[] = {
		{"exit", helpExit},
		{"env", helpEnv},
		{"cd", helpCd},
		{"setenv", helpSetenv},
		{"unsetenv", helpUnsetenv},
		{"help", helpHelp},
		{NULL, NULL}
	};
	register int i = 0, j = 1, arg_count = countArgs(build->args);
	bool foundCommand = false;

	if (arg_count == 1)
		return (helpmenu());
	while (j < arg_count)
	{
		i = 0;
		while (help_arr[i].cmd)
		{
			if (_strcmp(build->args[j], help_arr[i].cmd) == 0)
			{
				foundCommand = true;
				help_arr[i].func(build);
				break;
			}
			i++;
		}
		j++;
	}
	if (foundCommand == false)
	{
		errno = ENOBUILTIN;
		errorHandler(build);
	}
	return (1);
}

/**
 * helpmenu - give help options menu
 * Return: Always 1
 */
int helpmenu(void)
{
	char str[81] = "Type help [built-in]\n\nIncluded built-ins:";
	char *s = "\n\n\texit\n\tenv\n\tcd\n\tsetenv\n\tunsetenv\n\thelp\n";

	_strcat(str, s);
	write(STDOUT_FILENO, str, _strlen(str));
	return (1);
}


/**
 * helpExit - exiting shell instructions
 *
 * @build: build to provide instructions for
 *
 * Return: Always 1
 */
int helpExit(vars_t *build)
{
	char str[82] = "exit: exit [n]\n\tExit the shell.\n\n\t";
	char *str2 = "Exit with a status of n, or if n is omitted, 0.\n";

	(void)build;
	_strcat(str, str2);
	write(STDOUT_FILENO, str, _strlen(str));
	return (1);
}

/**
 * helpEnv - environment variables instructions
 *
 * @build: build to be used as input
 *
 * Return: Always 1
 */
int helpEnv(vars_t *build)
{
	char str[] = "env: env\n\tPrint the environment.\n";

	(void)build;
	write(STDOUT_FILENO, str, _strlen(str));
	return (1);
}
