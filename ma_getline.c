#include "shell.h"
/**
 * my_getline - Custom getline function
 * @lineptr: parameter
 * @n: parameter
 * @stream: parameter
 * Return: input
 */
ssize_t my_getline(char **lineptr, size_t *n, FILE *stream)
{
	static char buffer[BUFFER_SIZE];
	static size_t buffer_idx = 0;
	ssize_t read_count = 0;
	ssize_t line_len = 0;
	char c;

	if (*lineptr == NULL || *n == 0)
	{
		*n = BUFFER_SIZE;
		*lineptr = malloc(*n);
		if (*lineptr == NULL)
			return (-1);
	}
	while (1)
	{
		if (buffer_idx == 0)
		{
			read_count = read(fileno(stream), buffer, BUFFER_SIZE);
			if (read_count == -1)
				return (-1);
			if (read_count == 0)
			{
				if (line_len == 0)
					return (-1);
				else
					break;
			}
		}
        c = buffer[buffer_idx++];
	if (c == '\n')
	{
		(*lineptr)[line_len] = '\0';
		break;
	} else
	{
		(*lineptr)[line_len++] = c;
		if (line_len >= (ssize_t)(*n))
		{
			*n *= 2;
			*lineptr = realloc(*lineptr, *n);
			if (*lineptr == NULL)
				return (-1);
		}
	}
	}
	return (line_len);
}
