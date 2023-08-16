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
    char **argv = NULL;
    int count = 0;
    int in_arg = 0;
    char arg_buffer[512];
    size_t i;

    for (i = 0; cmd[i]; i++)
    {
        if (cmd[i] == ' ' && !in_arg)
        {
            continue;
        }
        else if (cmd[i] == ' ' && in_arg)
        {
            arg_buffer[count] = '\0';
            argv = realloc(argv, (count + 1) * sizeof(char *));
            argv[count] = _strdup(arg_buffer);
            count++;
            in_arg = 0;
        }
	else if (cmd[i] == '"')
        {
            i++;
            while (cmd[i] && cmd[i] != '"')
            {
                arg_buffer[in_arg] = cmd[i];
                in_arg++;
                i++;
            }
        }
        else
        {
            arg_buffer[in_arg] = cmd[i];
            in_arg++;
        }
    }

    if (in_arg)
    {
        arg_buffer[in_arg] = '\0';
        argv = realloc(argv, (count + 1) * sizeof(char *));
        argv[count] = _strdup(arg_buffer);
        count++;
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
		cmd[strcspn(cmd, "\n")] = '\0';
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
		if (cmd != NULL)
		{
		pid = fork();
		if (pid == -1)
		{
		perror("fork");
		exit(EXIT_FAILURE);
		}
		if (pid == 0)
		{
			execute_command(found_path ? found_path : argv[0], argv);
			exit(EXIT_SUCCESS);
		}
		if (waitpid(pid, &status, 0) == -1)
		{
			perror("wait");
			exit(EXIT_FAILURE);
		}
		}
		for (j = 0; j < argc; j++)
			free(argv[j]);
		free(argv);
		argc = 0;

	}
	free(cmd);

    return 0;
}
