#include "shell.h"

/**
 * _getenv - retrieves env variable that matches input string
 * @input: input string
 * @evn: local environmental variables
 * Return: string of env variable
 */
char *_getenv(char *input, char **evn)
{
	register int n = 0;
	char *tok, *right;

	while (evn[n])
	{
		tok = _strtok(evn[n], "=");
		if (_strcmp(tok, input) == 0)
		{
			right = _strtok(NULL, "=");
			return (right);
		}
		n++;
	}
	return (NULL);
}
