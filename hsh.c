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
        argv[count] = malloc(_strlen(str) + 1);
        _strcpy(argv[count], str);
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
	char *cmd = NULL, *cmd_cpy;
	size_t n = 0;
	char *str;
	char abs_path[256];
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
<<<<<<< HEAD
		if (strcmp(cmd, "exit") == 0)
			break;

=======
		if (_strcmp(cmd, "exit") == 0)
			exit(0);
>>>>>>> 60f702a5decf9291dd8361888c24fa5e79b4ab6e
		if (cmd[0] == '/')
			argv = split_input(cmd, &argc);
		else
		{
			cmd_cpy = malloc(_strlen(cmd) + 1);
			_strcpy(cmd_cpy, cmd);
			str = strtok(cmd_cpy, " ");
			_strcpy(abs_path, "/bin/");
			_strcat(abs_path, str);
			free(cmd_cpy);
			argv = split_input(abs_path, &argc);
		}
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
	}
	free(cmd);

    return 0;
}
