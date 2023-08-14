#include "shell.h"

#define MAX_PATH_LENGTH 1024

int is_cmd(const char *path)
{
    struct stat st;

    if (!path || stat(path, &st))
        return 0;

    if (st.st_mode & S_IFREG)
    {
        return 1;
    }
    return 0;
}

char *dup_chars(const char *pathstr, int start, int stop)
{
    static char buffer[1024];
    int i = 0, j = 0;

    for (j = 0, i = start; i < stop; i++)
        if (pathstr[i] != ':')
            buffer[j++] = pathstr[i];
    buffer[j] = 0;
    return buffer;
}

int starts_with(const char *str, const char *prefix)
{
    while (*prefix)
    {
        if (*str != *prefix)
            return 0;
        str++;
        prefix++;
    }
    return 1;
}
char *get_path(const char *command)
{
    const char *pathstr = getenv("PATH");
    int i = 0, start_pos = 0;
    char *path;
    char *temp;

    if (!pathstr || !command)
        return NULL;

    if ((strlen(command) > 2) && starts_with(command, "./"))
    {
        if (is_cmd(command))
            return strdup(command);
    }

    while (1)
    {
        if (!pathstr[i] || pathstr[i] == ':')
        {
            path = dup_chars(pathstr, start_pos, i);
            if (!*path)
            {
                path = strdup(command);
            }
            else
            {
                temp = (char *)malloc(strlen(path) + strlen(command) + 2);
                if (!temp)
                {
                    free(path);
                    return NULL;
                }
                strcpy(temp, path);
                strcat(temp, "/");
                strcat(temp, command);
                free(path);
                path = temp;
            }

            if (is_cmd(path))
                return path;

            if (!pathstr[i])
                break;

            start_pos = i + 1;
        }
        i++;
    }

    return NULL;
}
void execute_command(char **argv)
{
	char *executable = argv[0];
	extern char **environ;

	if (execve(executable, argv, environ) == -1)
	{
		perror("./shell");
		exit(EXIT_FAILURE);
	}
	free(environ);
}
