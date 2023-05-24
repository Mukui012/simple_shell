#include "shell.h"

/**
 * *_strcpy - copies the content of source string to destination string
 * @dest: destination string
 * @src: source string
 * Return: pointer to new string
 */
char *_strcpy(char *dest, char *src)
{
	char *temp = dest;

	while (*src)
		*dest++ = *src++;
	*dest = 0;
	return (temp);
}


/**
 * _strtok - parse strings separated by delimiter
 * @str: input string to be tokenized
 * @delim: separator
 * Return: pointer to first string
 */

char *_strtok(char *str, char *delim)
{
	static char *ptr; /* last pointer */
	char c;

	if (str == NULL)
		str = ptr;
	do {
		c = *str++;
		if (!c)
			return (NULL);
	} while (_strchr(delim, c));
	str--;
	ptr = str + _strcspn(str, delim);
	if (*ptr)
		*ptr++ = 0;
	return (str);
}

/**
 * _strcspn - returns first occurence of any char in
 * second string in first string
 * @string: input string
 * @chars: chars to check
 * Return: on success, pointer to first the first match
 */
int _strcspn(char *string, char *chars)
{
	char c;
	char *p, *s;

	for (s = string, c = *s; c; s++, c = *s)
		for (p = chars; *p; p++)
			if (c == *p)
				return (s - string);
	return (s - string);
}

/**
 * _strchr - find a character in a string
 * @s: input string
 * @c: target char
 * Return: on success, pointer to first occurrence of c, NULL otherwise
 */
char *_strchr(char *s, char c)
{
	char x;

	while (true)
	{
		x = *s++;
		if (x == c)
			return (s - 1);
		if (!x)
			return (NULL);
	}
}
