#include "shell.h"

/**
 * findinborns - find inbuilt commands and perform execution
 *
 * @build: input build
 *
 * Return: true on success, false otherwise
 */
bool findinborns(vars_t *build)
{
	register int i = 0;
	inborns_t getinborns[] = {
		{"exit", exitFunc},
		{"env", envFunc},
		{"cd", cdFunc},
		{"setenv", setenvFunc},
		{"unsetenv", unsetenvFunc},
		{"help", helpFunc},
		{NULL, NULL}
	};

	while (getinborns[i].cmd)
	{
		if (_strcmp(build->args[0], getinborns[i].cmd) == 0)
		{
			getinborns[i].func(build);
			freeArgsAndBuffer(build);
			return (true);
		}
		i++;
	}
	return (false);
}

/**
 * exitFunc - provide functionality to exit the application
 *
 * @build: input build
 *
 * Return: 1 on success, 0 otherwise
 */
int exitFunc(vars_t *build)
{
	register int arg_count, exit_status;

	arg_count = countArgs(build->args);
	if (arg_count == 1)
	{
		freeMembers(build);
		if (build->error)
			exit(build->error);
		exit(EXIT_SUCCESS);
	}
	else if (arg_count > 1)
	{
		exit_status = _atoi(build->args[1]);
		if (exit_status == -1)
		{
			errno = EILLEGAL;
			build->error = 2;
			errorHandler(build);
			return (0);
		}
		freeMembers(build);
		exit(exit_status);
	}
	return (1);
}
