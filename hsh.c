#include "shell.h"

/**
 * split_input - Split input command into arguments.
 *
 * @cmd: Input command string.
 * @argc: Pointer to store the argument count.
 *
 * Return: Array of arguments.
 */
char **split_input(char *cmd, int *argc)
{
    char *str;
    char **argv = NULL;
    int count = 0;

    str = strtok(cmd, " ");
    while (str)
    {
        argv = realloc(argv, (count + 1) * sizeof(char *));
        argv[count] = _strdup(str);
        count++;
        str = strtok(NULL, " ");
    }
    argv = realloc(argv, (count + 1) * sizeof(char *));
    argv[count] = NULL;

    *argc = count;
    return argv;
}
int main(void)
{
	char *cmd = NULL;
	size_t n = 0;
	char *found_path;
	pid_t pid;
	int argc = 0, status, j;
	char **argv = NULL;

	while (1)
	{
		write(1, "$ ", 2);
		if (getline(&cmd, &n, stdin) == -1)
		{
			perror("getline");
			break;
		}
		cmd[_strlen(cmd) - 1] = '\0';
		if (_strcmp(cmd, "exit") == 0)
			break;
		found_path = NULL;
		argv = split_input(cmd, &argc);
		if (argc > 0)
		{
			found_path = get_path(argv[0]);
			if (found_path == NULL)
			{
				printf("command not found\n");
				for (j = 0; j < argc; j++)
					free(argv[j]);
				free(argv);
				continue;
			}
		}	
		pid = fork();
		if (pid == -1)
		{
		perror("fork");
		exit(EXIT_FAILURE);
		}
		if (pid == 0)
		{
			if (execve(found_path ? found_path : argv[0], argv, NULL) == -1)
			{
				perror("execve");
				exit(EXIT_FAILURE);
			}
			exit(EXIT_SUCCESS);
		}
		if (waitpid(pid, &status, 0) == -1)
		{
			perror("wait");
			exit(EXIT_FAILURE);
		}
		for (j = 0; j < argc; j++)
			free(argv[j]);
		free(argv);
		argc = 0;
	}
	free(cmd);

    return 0;
}
