#include "shell.h"

/**
 * _strlen - returns the length of a string
 *
 * @s: input string
 *
 * Return: length of input string
 */
int _strlen(char *s)
{
	int len = 0;

	while (*s != '\0')
	{
		++len;
		++s;
	}
	return (len);
}

/**
 * _strcat - concatenates two strings
 * @dest: destination string
 * @src: source string
 * Return: concatenated string
 */
char *_strcat(char *dest, char *src)
{
	char *temp = dest + _strlen(dest);

	while (*src)
		*temp++ = *src++;
	*temp = 0;
	return (dest);
}

/**
 * _strcmp - compares if two strings are a match
 * @s1: input string 1
 * @s2: input string 2
 * Return: 1 on success, 0 otherwise
 */
int _strcmp(char *s1, char *s2)
{
	while (*s1)
	{
		if (*s1 != *s2)
			break;
		s1++;
		s2++;
	}

	return (*(unsigned char *)s1 - *(unsigned char *)s2);
}

/**
 * _strdup - duplicates the content of one string to another,
 * @str: string to be duplicated
 * Return: duplicated string
 */
char *_strdup(char *str)
{
	int i, len;
	char *str_copy;

	if (!str)
		return (NULL);
	len = _strlen(str);
	str_copy = malloc(sizeof(char) * len + 1);
	if (!str_copy)
	{
		perror("Malloc failed\n");
		exit(errno);
	}
	for (i = 0; i < len; i++)
		str_copy[i] = str[i];
	str_copy[i] = 0;
	return (str_copy);
}
