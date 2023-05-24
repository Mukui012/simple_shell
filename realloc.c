#include "shell.h"

/**
 * _realloc - reallocates memory block with malloc
 * @ptr: pointer to input string
 * @old_size: old pointer size
 * @new_size: new pointer size
 * Return: pointer to reallocated string
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	void *temp = NULL;

	if (new_size == old_size)
		return (ptr);
	if (!ptr)
	{
		free(ptr);
		temp = malloc(new_size);
		if (!temp)
		{
			perror("Malloc failed");
			exit(errno);
		}
		return (temp);
	}
	if (!new_size && ptr)
	{
		free(ptr);
		return (NULL);
	}
	temp = malloc(new_size);
	if (!temp)
	{
		perror("Malloc failed");
		exit(errno);
	}
	_memcpy(temp, ptr, old_size);
	free(ptr);
	return (temp);
}

/**
 * _memcpy - fills memory area
 * @dest: destination
 * @src: source
 * @n: number of bytes
 * Return: pointer to destination string
 */
char *_memcpy(char *dest, char *src, unsigned int n)
{
	char *temp = dest;

	while (n--)
		*dest++ = *src++;
	return (temp);
}
