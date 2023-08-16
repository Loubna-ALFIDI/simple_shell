#include "shell.h"

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

    path_token = strtok(path_copy, ":");

    while (path_token != NULL)
    {
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

        if (stat(file_path, &buffer) == 0)
        {
            free(path_copy);
            return file_path;
        }
        else
        {
            free(file_path);
            path_token = strtok(NULL, ":");
        }
    }

    free(path_copy);
    return NULL;
}

/**
 * execute_command - executes the given command
 * argv: command
 */
void execute_command(char *executable, char **argv)
{
    extern char **environ;
    char *built_in_path;
    int i;

    if (_strcmp(executable, "echo") == 0)
    {
        for (i = 1; argv[i] != NULL; i++)
        {
            printf("%s ", argv[i]);
        }
        printf("\n");
    } else
    {
	    built_in_path = get_path(executable);
	    if (built_in_path != NULL)
	    {
		    if (execve(built_in_path, argv, environ) == -1)
		    {
			    perror(built_in_path);
			    exit(EXIT_FAILURE);
		    }
            free(built_in_path);
	    }else
	    {
		if (execve(executable, argv, environ) == -1)
		{
			perror("executable");
			exit(EXIT_FAILURE);
		}
	    }
    }
    free(environ);
}
