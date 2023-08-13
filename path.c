#include "shell.h"

#define MAX_PATH_LENGTH 1024

char *get_path(const char *command)
{
	char *path = getenv("PATH");
	char *dir = strtok(path, ":");
	size_t dir_length, command_length;
	char *full_path;

    while (dir != NULL) {
        dir_length = strlen(dir);
        command_length = strlen(command);
        full_path = (char *)malloc(dir_length + command_length + 2);
        if (full_path == NULL) 
	{
            perror("malloc");
            exit(1);
        }
        strcpy(full_path, dir);
        strcat(full_path, "/");
        strcat(full_path, command);
        if (access(full_path, X_OK) == 0) {
            return full_path;
        }

        free(full_path);
        dir = strtok(NULL, ":");
    }

    return NULL;
}

/**
 * execute_command - execute command
 * @arg: args array
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
}
