#include "shell.h"

/**
 * checkPath - searches $PATH for directory of command
 * @build: input build
 * Return: true or false
 */
bool checkPath(vars_t *build)
{
	register int len;
	static char buffer[BUFSIZE];
	struct stat st;
	char *tok, *copy, *delim = ":", *temp;
	bool inLoop = false;

	if (checkEdgeCases(build))
		return (true);
	copy = _strdup(build->path);
	tok = _strtok(copy, delim);
	while (tok)
	{
		temp = inLoop ? tok - 2 : tok;
		if (*temp == 0 && stat(build->args[0], &st) == 0)
		{
			build->fpath = build->args[0];
			free(copy);
			return (true);
		}
		len = _strlen(tok) + _strlen(build->args[0]) + 2;
		_strcat(buffer, tok);
		_strcat(buffer, "/");
		_strcat(buffer, build->args[0]);
		insertNullByte(buffer, len - 1);
		if (stat(buffer, &st) == 0)
		{
			free(copy);
			build->fpath = buffer;
			return (true);
		}
		insertNullByte(buffer, 0);
		tok = _strtok(NULL, delim);
		inLoop = true;
	}
	build->fpath = build->args[0];
	free(copy);
	return (false);
}

/**
 * checkEdgeCases - helper function to check path to check edge cases
 * @build: input build
 * Return: true or false
 */
bool checkEdgeCases(vars_t *build)
{
	char *copy;
	struct stat st;

	copy = _strdup(build->path);
	if (!copy)
	{
		build->fpath = build->args[0];
		free(copy);
		return (true);
	}
	if (*copy == ':' && stat(build->args[0], &st) == 0)
	{
		build->fpath = build->args[0];
		free(copy);
		return (true);
	}
	free(copy);
	return (false);
}