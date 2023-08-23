#include "shell.h"
#include <signal.h>
void free_argv(char **argv, int argc)
{
	int i;

    for (i = 0; i < argc; i++)
        free(argv[i]);
    free(argv);
}

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
	int count = 0, quotes = 0, quote_type = '\0';
	size_t i;

	str = strtok(cmd, " ");
	while (str)
	{
		if (str[0] == '"' || str[0] == '\'')
		{
			quotes = 1;
			quote_type = str[0];
			for (i = 0; i < (size_t)(_strlen(str)); i++)
				str[i] = str[i + 1];
		}
		if (quotes && str[_strlen(str) - 1] == quote_type)
		{
			str[_strlen(str) - 1] = '\0';
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
	return (argv);
}

/**
 * sigint_handler - handles the case when the program gets imterrupted
 */
void sigint_handler(int signum)
{
        (void)signum;
	write(STDOUT_FILENO, "\n$ ", 4);
        exit(EXIT_SUCCESS);
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
	int argc = 0, status;
	char **argv = NULL;
	struct stat buffer;

	signal(SIGINT, sigint_handler);
	while (1)
	{
		write(1, "$ ", 2);
		if (getline(&cmd, &n, stdin) == -1)
		{
			if (cmd != NULL)
			{
				free(cmd);
				cmd = NULL;
				continue;
				/*break;*/
			}
			perror("getline");
			break;
		}
		if (_strlen(cmd) > 0 && cmd[_strlen(cmd) - 1] == '\n')
			cmd[_strlen(cmd) - 1] = '\0';
		if (_strlen(cmd) == 0)
		{
			free(cmd);
			cmd = NULL;
			continue;
		}
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
				free_argv(argv,argc);
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
					execute_command(argv);
					free(found_path);
					free_argv(argv, argc);
					exit(EXIT_FAILURE);
				}
			}
			if (waitpid(pid, &status, 0) == -1)
			{
				perror("wait");
				exit(EXIT_FAILURE);
			}
		}
		if (found_path && (stat(argv[0], &buffer)))
			free(found_path);
		free_argv(argv,argc);
		argc = 0;
		free(cmd);
		cmd = NULL;

	}
	free(cmd);
	return (0);
}
