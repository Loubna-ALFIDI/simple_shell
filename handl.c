#include "shell.h"
/**
 * echo - Handle the "echo" command.
 *
 * @cmd: Input command string.
 */
void echo(char *cmd)
{
	/*char c; */
	char *str = cmd + _strlen("echo ");
/**
 * int str_length = _strlen(str), i;

 *	for (i = 0; i < str_length; i++)
 *		write(1, &c, 1);
 *	write(1, "\n", 1);
 */
	  while (*str != '\0') {
        write(1, str, 1);
        str++;
    }

    write(1, "\n", 1);

}

