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

        // Allocate memory for the full path
        full_path = (char *)malloc(dir_length + command_length + 2); // 1 for '/' and 1 for '\0'
        if (full_path == NULL) {
            perror("malloc");
            exit(1);
        }

        // Copy the directory path and command to the full path
        strcpy(full_path, dir);
        strcat(full_path, "/");
        strcat(full_path, command);

        // Check if the full path is executable
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
void execute_command(char **arg)
{
    char *command = get_path(arg[0]);
    int j = execve(command, arg, NULL);

    if (j == -1)
    {
        perror(arg[0]);
        exit(1);
    }
    free(command);
}
