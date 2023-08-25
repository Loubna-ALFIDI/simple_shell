#include "shell.h"

/**
 * my_free_argv - frees argv
 * @argv: array of args
 */
void my_free_argv(char **argv)
{
	int i;

	if (argv == NULL)
		return;
	for (i = 0; argv[i] != NULL; i++)
		free(argv[i]);
	free(argv);
}

/**
 * is_digit - checks if c is a digit
 * @c: char
 */
bool is_digit(char c)
{
	return c >= '0' && c <= '9';
}

/**
 * handle_exit - exit built-in funcion
 * @argv: array of args
 * @argc: arg count
 */
void handle_exit(char **argv, int argc)
{
	int exit_status = 0;
	char *str;

	if (argc > 1 && argv[1] != NULL)
	{
		str = argv[1];
		while (*str != '\0')
		{
			if (!is_digit(*str))
			{
				_puts("Invalid exit status: ");
				_puts(argv[1]);
				free_argv(argv, argc);
				exit(EXIT_FAILURE);
			}
			str++;
		}
		exit_status = my_atoi(argv[1]);
	}
	free_argv(argv, argc);
	exit(exit_status);
}
