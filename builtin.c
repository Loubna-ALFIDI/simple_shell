#include "shell.h"

/**
 * builtin_env - Prints the current environment variables.
 */
void builtin_env(void)
{
	char **env;

	for (env = environ; *env != NULL; env++)
	{
		write(1, *env, _strlen(*env));
		write(1, "\n", 1);
	}
}
