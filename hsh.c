#include "shell.h"
#include <signal.h>

/**
 * free_argv - frees args
 * @argv: array of args
 * @argc: args count
 */
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
char **split_input(char cmd[], int *argc)
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
			argv[count] = _strdup(str);
			if (argv[count] == NULL)
			{
				perror("Memory allocation error");
				exit(EXIT_FAILURE);
			}
			count++;
		}
		str = strtok(NULL, " ");
	}
	if (count > 0)
	{
		argv = realloc(argv, (count + 1) * sizeof(char *));
		argv[count] = NULL;
	}
	*argc = count;
	return (argv);
}

/**
 * sigint_handler - handles the case when the program gets imterrupted
 * @signum: signal number
 */
void sigint_handler(int signum)
{
	(void)signum;
	write(STDOUT_FILENO, "\n$ ", 4);
}

/**
 * non_interactive - handles non interactive
 */
void non_interactive(void)
{
	char *cmd = NULL;
	size_t n = 0;
	char error_msg[50];
	ssize_t line_read;
	char *found_path;
	pid_t pid;
	int argc = 0, status;
	char **argv = NULL;
	struct stat buffer;

	line_read = my_getline(&cmd, &n, stdin);
	if (line_read == -1)
	{
		write(1, "\n", 1);
		free(cmd);
		exit(1);
	}
	if (_strlen(cmd) > 0 && cmd[_strlen(cmd) - 1] == '\n')
		cmd[_strlen(cmd) - 1] = '\0';
	if (_strlen(cmd) == 0)
	{
		free(cmd);
		cmd = NULL;
		exit(1);
	}
	if (_strcmp(cmd, "env") == 0)
		builtin_env();
	if (_strcmp(cmd, "exit") == 0)
	{
		exit(1);
	}
	found_path = NULL;
	argv = split_input(cmd, &argc);
	if (argc > 0)
	{
		found_path = get_path(argv[0]);
		if (found_path == NULL)
		{
			/*perror("./shell");*/
			_itoa(__LINE__, error_msg, 10);
			_strcat(error_msg, ": ");
			_strcat(error_msg, argv[0]);
			_strcat(error_msg, ": not found\n");
			write(STDERR_FILENO, "./hsh: ", 7);
			write(STDERR_FILENO, error_msg, _strlen(error_msg));
			free_argv(argv, argc);
			exit(1);
		}
	} else
	{
		free(cmd);
		cmd = NULL;
		exit(1);
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
				/*ecute_command(argv);*/
				_itoa(__LINE__, error_msg, 10);
				_strcat(error_msg, ": ");
				_strcat(error_msg, argv[0]);
				_strcat(error_msg, ": not found\n");
				write(STDERR_FILENO, "./hsh: ", 7);
				write(STDERR_FILENO, error_msg, _strlen(error_msg));
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
	free_argv(argv, argc);
	argc = 0;
	free(cmd);
	cmd = NULL;
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
	char error_msg[50];
	ssize_t line_read;
	char *found_path;
	pid_t pid;
	int argc = 0, status;
	char **argv = NULL;
	struct stat buffer;

	signal(SIGINT, sigint_handler);
	if (isatty(STDIN_FILENO) == 1)
	{
	while (1)
	{
		write(1, "$ ", 2);
		line_read = getline(&cmd, &n, stdin);
		if (line_read == -1)
		{
			write(1, "\n", 1);
			free(cmd);
			exit(1);
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
			builtin_env();
		if (_strcmp(cmd, "exit") == 0)
		{
			handle_exit(argv, argc);
			break;
		}
		found_path = NULL;
		argv = split_input(cmd, &argc);
		if (argc > 0)
		{
			found_path = get_path(argv[0]);
			if (found_path == NULL)
			{
				/*perror("./shell");*/
				_itoa(__LINE__, error_msg, 10);
				_strcat(error_msg, ": ");
				_strcat(error_msg, argv[0]);
				_strcat(error_msg, ": not found\n");
				write(STDERR_FILENO, "./hsh: ", 7);
				write(STDERR_FILENO, error_msg, _strlen(error_msg));
				free_argv(argv, argc);
				continue;
			}
		} else
		{
			free(cmd);
			cmd = NULL;
			continue;
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
					_itoa(__LINE__, error_msg, 10);
					_strcat(error_msg, ": ");
					_strcat(error_msg, argv[0]);
					_strcat(error_msg, ": not found\n");
					write(STDERR_FILENO, "./hsh: ", 7);
					write(STDERR_FILENO, error_msg, _strlen(error_msg));
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
		free_argv(argv, argc);
		argc = 0;
		free(cmd);
		cmd = NULL;
	}
	free(cmd);
	}
	else
		non_interactive();
	return (0);
}
