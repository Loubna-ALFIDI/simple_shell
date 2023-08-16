#include "shell.h"

/**
 * builtin_env - Prints the current environment variables.
 */
void builtin_env(void)
{
	extern char **environ;
	char **env;

	for (env = environ; *env != NULL; env++)
	{
		write(1, *env, strlen(*env));
		write(1, "\n", 1);
	}
}
