#include "shell.h"

/**
 * updEnviron - change enviroment variables
 * @build: input build
 * Return: true(success) false(failure)
 */
bool updEnviron(vars_t *build)
{
	register int n;

	n = updold(build);
	updcur(build, n);
	return (true);
}

/**
 * updold - updates OLDPWD to current PWD
 * @build: input build
 * Return: index in linked list of PWD on success
 * Or return -1 for failure
 */
int updold(vars_t *build)
{
	register int pwdIndex = 0, index = 0;
	static char old[BUFSIZE];
	char *current = NULL;

	_strcat(old, "OLD");
	pwdIndex = searchNode(build->environment, "PWD");
	if (pwdIndex == -1)
	{
		return (-1);
	}
	current = getNodeAtIndex(build->environment, pwdIndex);
	_strcat(old, current);
	insert_null_byte(old, _strlen(current) + 4);
	free(current);
	index = searchNode(build->environment, "OLDPWD");
	if (index == -1)
	{
		return (-1);
	}
	deleteNodeAtIndex(&build->environment, index);
	addNodeAtIndex(&build->environment, index, old);
	insert_null_byte(old, 0);
	return (pwdIndex);
}

/**
 * updcur - updates PWD to accurately reflect current directory
 * @build: input build
 * @index: index in linked list of where to insert PWD enviroment var
 * Return: true on success, false on failure
 */
bool updcur(vars_t *build, int index)
{
	static char tmp[BUFSIZE], cwd[BUFSIZE];

	getcwd(tmp, BUFSIZE);
	_strcat(cwd, "PWD=");
	_strcat(cwd, tmp);
	if (index > -1)
	{
		deleteNodeAtIndex(&build->environment, index);
		addNodeAtIndex(&build->environment, index, cwd);
	} else
		addNodeAtIndex(&build->environment, 0, cwd);
	insert_null_byte(tmp, 0);
	insert_null_byte(cwd, 0);
	return (true);
}
