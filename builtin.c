#include "shell.h"

/**
 * builtin_env - Prints the current environment variables.
 */
void builtin_env(void)
{
	char **env = environ;
	int i = 0;

	for (i = 0; env[i] != NULL; i++)
	{
		write(1, *env, _strlen(env[i]));
		write(1, "\n", 1);
	}
}
