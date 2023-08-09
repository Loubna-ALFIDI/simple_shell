#include <shell.h>

/**
 * _puts - prints a string followed by a new line
 * @str: is a parameter
 * Retur: void
 */
void _puts(char *str)
{
	while (*str != '\0')
	{
		_putchar(*str);
		str++;
	}
	_putchar('\n');
}

/**
 * putchar - writes the character c to stdout
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putchar(char c)
{
	return (write(1, &c, 1));
}

/**
 * _strlen - returns the length of a string
 * @s: is a parameter
 * Return: int
 */
int _strlen(char *s)
{
	int l;

	l = 0;
	while (*s != '\0')
	{
		l++;
		s++;
	}
	return (l);
}

/**
 * _strcpy - check the code
 * @dest: parametre
 * @src: parametre
 * Return: Always 0.
 */
char *_strcpy(char *dest, char *src)
{
	int i;

	for (i = 0; src[i] != '\0'; i++)
	{
		dest[i] = src[i];
	}
	dest[i++] = '\0';
	return (dest);
}

/**
 * _strcmp - compares two strings
 * @s1: is a parameter
 * @s2: is a parameter
 * Return: int
 */
int _strcmp(char *s1, char *s2)
{
	int i = 0, j;

	while (s1[i] == s2[i] && s1[i] != '\0')
		i++;
	j = s1[i] - s2[i];
	return (j);
}
