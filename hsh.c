#include "shell.h"

int main (void)
{
	char *cmd = NULL, *cmd_cpy = NULL, *token = NULL;
	char *str;
	size_t n = 0;
	pid_t pid;
	int argc = 0, i = 0, status;
	char **argv = NULL;

	while (1)
	{
		write(1,"$ ", 2);
		if (getline(&cmd, &n, stdin) == -1)
		{
			perror("getline");
			return (-1);
		}
		cmd[i - 1] = '\0';
		str = strtok(cmd, " ");
		cmd_cpy = strdup(cmd);

		while (str)
		{
			argv = realloc(argv, (argc + 1) * sizeof(char *));
			argv[argc] = malloc(_strlen(str) + 1);
			_strcpy(argv[argc], str);
			argc++;
			str = strtok(NULL, " ");
		}
		argv = realloc(argv, (argc + 1) * sizeof(char *));
		argv[argc] = NULL;

		pid = fork();
		if (pid == -1)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		if (pid == 0)
			execute_command(argv);
		if (waitpid(pid, &status, 0) == -1)
		{
			perror("wait");
			exit(EXIT_FAILURE);
		}
		for (int j = 0; j < argc; j++)
			free(argv[j]);
		free(argv);
		argc = 0;
	}
	free(cmd);
	free(cmd_cpy);

	return (0);
}
