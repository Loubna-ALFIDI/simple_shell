#include "shell.h"
void my_free_argv(char **argv)
{
	int i;

	if (argv == NULL)
		return;
	for (i = 0; argv[i] != NULL; i++)
		free(argv[i]);
	free(argv);
}
bool is_digit(char c)
{
	return c >= '0' && c <= '9';
}
void handle_exit(char **argv)
{
	int exit_status = 0;
	char *str;

	if (argv[1] != NULL)
	{
		str = argv[1];
		while (*str != '\0')
		{
			if (!is_digit(*str))
			{
				fprintf(stderr, "Invalid exit status: %s\n", argv[1]);
				exit(EXIT_FAILURE);
			}
			str++;
		}
		exit_status = my_atoi(argv[1]);
		free(argv);
		if (argv != NULL)
			my_free_argv(argv);
	}
	
	exit(exit_status);
}
