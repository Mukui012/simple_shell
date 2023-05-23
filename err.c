#include "shell.h"

/**
 * errorHandler - prints error message from shell
 * @build: build vars_t
 */
void errorHandler(vars_t *build)
{
	register int len;
	static char error[BUFSIZE];
	char *ptr, *alp;

	alp = itoa(build->count);
	_strcat(error, build->shellName);
	_strcat(error, ": ");
	_strcat(error, alp);
	_strcat(error, ": ");
	_strcat(error, build->args[0]);
	_strcat(error, getErrorMessage());
	if (build->args[1])
	{
		if (errno != EBADCD)
			_strcat(error, ": ");
		_strcat(error, build->args[1]);
	}
	_strcat(error, "\n");
	ptr = _strchr(error, '\n');
	len = ptr - error;
	write(STDERR_FILENO, error, len + 1);
	free(alp);
	insertNullByte(error, 0);
}

/**
 * getErrorMessage - matches errno to corresponding string
 * Return: string of error message
 */
char *getErrorMessage(void)
{
	char *str;

	switch (errno)
	{
		case EBADCD:
			str = ": No such file or directory ";
			break;
		case ENOENT:
			str = ": command not found";
			break;
		case ENOSTRING:
			str = ": bad variable name";
			break;
		case EILLEGAL:
			str = ": Illegal number";
			break;
		case EWSIZE:
			str = ": invalid number of arguments";
			break;
		case ENOBUILTIN:
			str = ": type help for a list of built-ins";
			break;
		case EACCES:
			str = ": Permission denied";
			break;
		default:
			str = ": no error number assigned";
	}
	return (str);
}

/**
 * countDigits - count number of digits in a number
 * @num: input number
 * Return: number of digits
 */
unsigned int countDigits(int num)
{
	register int symbols = 0;

	while (num > 0)
	{
		symbols++;
		num /= 10;
	}
	return (symbols);
}

/**
 * itoa - converts integer to string
 * @num: input integer
 * Return: string type of number
 */
char *itoa(unsigned int num)
{
	register int numerals = 0;
	char *str;

	numerals += countDigits(num);
	str = malloc(sizeof(char) * (numerals + 1));
	if (!str)
	{
		perror("Malloc: failed\n");
		exit(errno);
	}
	insertNullByte(str, numerals);
	while (num > 0)
	{
		str[numerals - 1] = num % 10 + '0';
		num = num / 10;
		numerals--;
	}
	return (str);
}
