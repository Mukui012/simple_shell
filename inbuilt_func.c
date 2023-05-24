#include "shell.h"

/**
* countArgs - counts arguments in string
* @args: pointer to array of strings
* Return: on success, argument count
*/
int countArgs(char **args)
{
	register int i = 0;

	while (args[i])
		i++;
	return (i);
}

/**
* _atoi - explicitly converts string to an integer
* @s: string input
* Return: converted number on succes, -1 otherwise
*/
int _atoi(char *s)
{
	register int i = 0;
	unsigned long num = 0;

	while (s[i])
	{
		if (s[i] >= '0' && s[i] <= '9')
			num = num * 10 + s[i] - '0';
		else
			return (-1);
		i++;
	}
	if (num > INT_MAX)
	{
		return (-1);
	}
	return (num);
}
