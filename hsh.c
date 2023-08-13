#include "shell.h"
void execute_command_with_path(char **argv)
{
    char *full_path = get_path(argv[0]);
    if (full_path) {
        pid_t pid = fork();
        if (pid == -1) {
            perror("fork");
            free(full_path);
            exit(EXIT_FAILURE);
        }
        if (pid == 0) {
            if (execve(full_path, argv, NULL) == -1) {
                perror("execve");
                free(full_path);
                exit(EXIT_FAILURE);
            }
        }
        if (waitpid(pid, NULL, 0) == -1) {
            perror("waitpid");
            free(full_path);
            exit(EXIT_FAILURE);
        }
        free(full_path);
    } else {
        printf("Command not found: %s\n", argv[0]);
    }
}
int _getchar()
{
    char c;
    while (read(STDIN_FILENO, &c, 1) == -1) {
        if (errno == EINTR) {
            continue;
        } else {
            perror("read");
            exit(EXIT_FAILURE);
        }
    }
    return c;
}
/**
 * main - Entry point
 *
 * Return: 0.
 */
int main (void)
{
	char *cmd = NULL, *cmd_cpy = NULL;
	char *str;
	size_t n = 0;
	int argc = 0, j, c;
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
		cmd_cpy = _strdup(cmd);
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
		free(cmd_cpy);
		if (argc > 0)
		{
			execute_command_with_path(argv);
		}
		for (j = 0; j < argc; j++)
			free(argv[j]);
		free(argv);
		argc = 0;
		while ((c = _getchar()) != '\n' && c != EOF);
	}
	free(cmd);

	return (0);
}
