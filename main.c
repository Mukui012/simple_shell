#include "shell.h"

/**
 * shell - simple shell
 * @build: input build
 * Return: nothing
 */
void shell(vars_t *build)
{
	while (true)
	{
		get_line(build);
		if (splitString(build) == false)
			continue;
		if (findinborns(build) == true)
			continue;
		checkPath(build);
		forkAndExecute(build);
	}
}

/**
 * get_line - check user input and display prompt
 * @build: input build
 * Return: Nothing
 */
void get_line(vars_t *build)
{
	register int len;
	size_t buffer = 0;
	char *ptr, *temp;

	build->args = NULL;
	build->enviromentList = NULL;
	build->count++;
	if (isatty(STDIN_FILENO))
		displayPrompt();
	len = getline(&build->buffer, &buffer, stdin);
	if (len == EOF)
	{
		freeMembers(build);
		if (isatty(STDIN_FILENO))
			displayNewLine();
		if (build->error)
			exit(build->error);
		exit(EXIT_SUCCESS);

	}
	ptr = _strchr(build->buffer, '\n');
	temp = _strchr(build->buffer, '\t');
	if (ptr || temp)
		insertNullByte(build->buffer, len - 1);
	stripComments(build->buffer);
}

/**
 * stripComments - get rid of comments in string
 * @str: input string
 * Return: remaining length
 */
void stripComments(char *str)
{
	register int i = 0;
	bool not_first = false;

	while (str[i])
	{
		if (i == 0 && str[i] == '#')
		{
			insertNullByte(str, i);
			return;
		}
		if (not_first)
		{
			if (str[i] == '#' && str[i - 1] == ' ')
			{
				insertNullByte(str, i);
				return;
			}
		}
		i++;
		not_first = true;
	}
}

/**
 * forkAndExecute - create child process and execute
 * @build: input build
 * Return: nothing
 */
void forkAndExecute(vars_t *build)
{
	int status;
	pid_t my_pid = fork();

	convertLLtoArr(build);
	if (my_pid == -1)
	{
		perror("error\n");
		freeMembers(build);
		freeArgs(build->enviromentList);
		exit(1);
	}
	if (my_pid == 0)
	{
		if (execve(build->fpath, build->args, build->enviromentList) == -1)
		{
			errorHandler(build);
			freeMembers(build);
			freeArgs(build->enviromentList);
			if (errno == ENOENT)
				exit(127);
			if (errno == EACCES)
				exit(126);
		}
	}
	else
	{
		wait(&status);
		if (WIFEXITED(status))
			build->error = WEXITSTATUS(status);
		freeArgsAndBuffer(build);
		freeArgs(build->enviromentList);
	}
}

/**
 * convertLLtoArr - convert items in linked list to array
 * @build: input build
 * Return: nothing
 */
void convertLLtoArr(vars_t *build)
{
	register int i = 0;
	size_t item_count = 0;
	char **env_list = NULL;
	lin_t *temp = build->enviroment;

	item_count = list_len(build->enviroment);
	env_list = malloc(sizeof(char *) * (item_count + 1));
	if (!env_list)
	{
		perror("Malloc failed\n");
		exit(1);
	}
	while (temp)
	{
		env_list[i] = _strdup(temp->str);
		temp = temp->nxt;
		i++;
	}
	env_list[i] = NULL;
	build->env_list = env_list;
}
