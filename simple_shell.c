#include "shell.h"


/**
 * vars_tInit - call value for members of struct
 *
 * @build: the input build for the struct
 *
 * Return: initialized members of struct
 */
vars_t *vars_tInit(vars_t *build)
{
	build->environment = generateLinkedList(environ);
	build->environmentList = NULL;
	build->args = NULL;
	build->buffer = NULL;
	build->path = _getenv("PATH", environ);
	build->fpath = NULL;
	build->count = 0;
	build->shellName = NULL;
	build->error = 0;
	return (build);
}

/**
 * main - program entry point for the simple unix shell
 *
 * @ac: the argument count
 * @av: the argument vector
 *
 * Return: 0 on success
 */
int main(int ac, char **av)
{
	vars_t build;

	(void)ac;
	signal(SIGINT, sigintHandler);
	vars_tInit(&build);
	build.shellName = av[0];
	shell(&build);
	return (0);
}

