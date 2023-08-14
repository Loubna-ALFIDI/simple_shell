#include "shell.h"

#define MAX_PATH_LENGTH 1024

char *get_path(const char *command)
{

	char *path = getenv("PATH");
	char *dir = strtok(path, ":");
	size_t dir_length, command_length = strlen(command);
	char *full_path = malloc(MAX_PATH_LENGTH);

	while (dir != NULL)
	{
		dir_length = strlen(dir);
		if (dir_length + command_length + 2 > MAX_PATH_LENGTH)
		{
			_puts("path too long");
			exit(1);
		}
		strcpy(full_path, dir);
		strcat(full_path, "/");
		strcat(full_path, command);
		if (access(full_path, X_OK) == 0)
		{
	    		return(full_path);
		}
		dir = strtok(NULL, ":");
	}
	free(full_path);

	return(NULL);
}
void execute_command(char **argv)
{
	char *executable = argv[0];
	extern char **environ;

	if (execve(executable, argv, environ) == -1)
	{
		perror("./shell");
		exit(EXIT_FAILURE);
	}
	free(environ);
}
