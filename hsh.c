#include "shell.h"

int main (void)
{
	char *cmd = NULL;
	char *str;
	size_t n = 0;
	pid_t pid;
	int argc = 0, status, j;
	char **argv = NULL;

	while (1)
	{
		write(1,"$ ", 2);
		if (getline(&cmd, &n, stdin) == -1)
		{
			perror("getline");
			break;
		}
		cmd[_strlen(cmd) - 1] = '\0';
		str = strtok(cmd, " ");
		argv = NULL;
		argc = 0;

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
		for (j = 0; j < argc; j++)
			free(argv[j]);
		free(argv);
		argc = 0;
		free(cmd);
	}
	free(cmd);

	return (0);
}
