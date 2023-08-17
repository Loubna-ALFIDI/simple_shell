#include "shell.h"

/**
 * split_input - splits an input command string into arguments.
 * @cmd: command
 * @argc: arg count
 * Return: array of args
 */
char **split_input(char *cmd, int *argc)
{
    char *str;
    char **argv = NULL;
    int count = 0;
    int quotes = 0;
    int quote_type = '\0';
    size_t i;

    str = strtok(cmd, " ");
    while (str)
    {
        if (str[0] == '"' || str[0] == '\'')
        {
            quotes = 1;
            quote_type = str[0];

            for (i = 0; i < strlen(str); i++)
            {
                str[i] = str[i + 1];
            }
        }

        if (quotes && str[strlen(str) - 1] == quote_type)
        {

            str[strlen(str) - 1] = '\0';
            quotes = 0;
            quote_type = '\0';
        }

        if (!quotes)
        {
            argv = realloc(argv, (count + 1) * sizeof(char *));
            argv[count] = strdup(str);
            if (argv[count] == NULL)
            {
                perror("Memory allocation error");
                exit(EXIT_FAILURE);
            }
            count++;
        }

        str = strtok(NULL, " ");
    }

    argv = realloc(argv, (count + 1) * sizeof(char *));
    argv[count] = NULL;

    *argc = count;
    return argv;
}
/**
 * main - Entry point
 *
 * Return: 0.
 */
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
		if (_strcmp(cmd, "env") == 0)
		{
			builtin_env();
		}
		if (_strcmp(cmd, "exit") == 0)
			break;
		found_path = NULL;
		argv = split_input(cmd, &argc);
		if (argc > 0)
		{
			found_path = get_path(argv[0]);
			if (found_path == NULL)
			{
				perror("./shell");
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
				if (execve(found_path ? found_path : argv[0], argv, NULL) == -1)
				{
					perror("execve");
					exit(EXIT_FAILURE);
				}
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
	return (0);
}
