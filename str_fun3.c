#include "shell.h"

/**
 * splitString - tokenize strings at space delimiter, adds them to array
 * @build: input build
 * Return: true on success
 */
bool splitString(vars_t *build)
{
	register unsigned int i = 0;
	char *token, *str_copy;

	if (countWords(build->buffer) == 0)
	{
		build->args = NULL;
		free(build->buffer);
		return (false);
	}
	build->args = malloc((countWords(build->buffer) + 1) * sizeof(char *));
	str_copy = _strdup(build->buffer);
	token = _strtok(str_copy, " ");
	while (token)
	{
		build->args[i] = _strdup(token);
		token = _strtok(NULL, " ");
		i++;
	}
	build->args[i] = NULL;
	free(str_copy);
	return (true);
}

/**
 * countWords - counts the words in a string
 *
 * @str: input string
 *
 * Return: word count
 */
unsigned int countWords(char *str)
{
	register int words = 0;
	bool is_word = false;

	while (*str)
	{
		if (isSpace(*str) && is_word)
			is_word = false;
		else if (!isSpace(*str) && !is_word)
		{
			is_word = true;
			words++;
		}
		str++;
	}
	return (words);
}

/**
 * isSpace - check for space in string
 * @c: input character
 * Return: true or false
 */
bool isSpace(char c)
{
	return (c == ' ');
}
