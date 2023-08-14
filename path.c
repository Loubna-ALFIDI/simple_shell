#include "shell.h"

/**
 * get_path - takes command and returns its path
 * command: the command
 * Return: the path
 */
char *get_path(char *command)
{
	char *path, *path_copy, *path_token, *file_path;
	struct stat buffer;

	if (stat(command, &buffer) == 0)
		return _strdup(command);
	path = getenv("PATH");
	if (path == NULL)
        	return NULL;
	path_copy = strdup(path);
	if (path_copy == NULL)
		return NULL;
	if (path)
	{
		path_copy = _strdup(path);

		path_token = strtok(path_copy, ":");

		while(path_token != NULL)
		{
			/* file_path = malloc(directory_length + command_length + 2);*/
			file_path = malloc(strlen(path_token) + strlen(command) + 2);
			if (file_path == NULL)
			{
				perror("malloc");
				free(path_copy);
				return NULL;
			}
			_strcpy(file_path, path_token);
			_strcat(file_path, "/");
			_strcat(file_path, command);
			_strcat(file_path, "\0");
			if (stat(file_path, &buffer) == 0)
			{				
				free(path_copy);				
				return (file_path);
			}
			else
			{
				free(file_path);
				path_token = strtok(NULL, ":");
			}
		}
		free(path_copy);
		if (stat(command, &buffer) == 0)
		{
			return (command);
		}
		return (NULL);
	}
	free(path_copy);
	return (NULL);
}

/**
 * execute_command - executes the given command
 * argv: command
 */
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
