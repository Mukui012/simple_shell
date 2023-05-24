#include "shell.h"

/**
 * envFunc - prints the enviroment
 * @build: input
 * Return: Always 1
 */
int envFunc(vars_t *build)
{
		printList(build->environment);
		return (1);
}

/**
 * setenvFunc - adds env variable if it does not exist,
 * and modifies env variable if it exists
 * @build: input build
 * Return: Always 1
 */
int setenvFunc(vars_t *build)
{
	register int index, len;
	static char buffer[BUFSIZE];

	if (countArgs(build->args) != 3)
	{
		errno = EWSIZE;
		errorHandler(build);
		return (1);
	}
	len = _strlen(build->args[1]) + _strlen(build->args[2]) + 2;
	_strcat(buffer, build->args[1]);
	_strcat(buffer, "=");
	_strcat(buffer, build->args[2]);
	insert_null_byte(buffer, len - 1);
	index = searchNode(build->environment, build->args[1]);
	if (index == -1)
	{
		addNodeEnd(&build->environment, buffer);
		insert_null_byte(buffer, 0);
		return (1);
	}
	deleteNodeAtIndex(&build->environment, index);
	addNodeAtIndex(&build->environment, index, buffer);
	insert_null_byte(buffer, 0);
	return (1);
}

/**
 * unsetenvFunc - deletes existing env variable,
 * while only accepting valid variable names
 * @build: input build
 * Return: Always 1
 */
int unsetenvFunc(vars_t *build)
{
	register int var, i = 1;
	bool match = false;

	while (build->args[i])
	{
		if (_isalpha(build->args[i][0]) || build->args[i][0] == '_')
		{
			var = searchNode(build->environment, build->args[i]);
			if (var > -1)
			{
				deleteNodeAtIndex(&build->environment, var);
				match = true;
			}
		}
		i++;
	}
	if (match == false)
	{
		errno = ENOSTRING;
		errorHandler(build);
	}
	return (1);
}

/**
 * _isalpha - checks if c is an alphabetic character
 * @c: character to be checked
 * Return: 1 if c is a letter, 0 if otherwise
 */
int _isalpha(int c)
{
	if (c > 64 && c < 91)
		return (1);
	else if (c > 96 && c < 123)
		return (1);
	else
		return (0);
}
