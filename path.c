#include "shell.h"

/**
 * get_path - get full path of a given command.
 * @command: the command
 * Return: path.
 */
char *get_path(char *command)
{
	char *path, *path_copy, *path_token, *file_path;
	struct stat buffer;

	if (stat(command, &buffer) == 0)
		return (_strdup(command));
	path = _getenv("PATH");
	if (path == NULL)
		return (NULL);
	path_copy = _strdup(path);
	if (path_copy == NULL)
		return (NULL);		  
	path_token = strtok(path_copy, ":");
	while(path_token != NULL)
	{
		file_path = malloc(_strlen(path_token) + _strlen(command) + 2 + 1);
		if (file_path == NULL)
		{
			perror("malloc");
			free(path_copy);
			free(command);
			return (NULL);
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
	/*free(file_path);*/
	return (NULL);
}

/**
 * execute_command - executes the given command
 * argv: command
 */
void execute_command(char **argv)
{
	char *executable = argv[0];

	if (execve(executable, argv, NULL) == -1)
	{
		perror("./shell");
		exit(EXIT_FAILURE);
	}
}

/**
 * _getenv - same as getenv
 * @name: string
 * Return: string
 */
char *_getenv(char *name)
{
	extern char **environ;
	char **env = environ;
	char *value = NULL;
	int len = _strlen(name);

	while (*env != NULL)
	{
		char *var = *env;
		int j;

		for (j = 0; j < len; j++)
		{
			if (name[j] != var[j])
				break;
		}

		if (j == len && var[j] == '=')
		{
			value = var + len + 1;
			break;
		}

		env++;
	}

	return value;
}

