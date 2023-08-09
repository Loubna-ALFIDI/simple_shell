#include "shell.h"
#include <stdlib.h>

/**
 * _strdup - check the code
 * @str: parametre
 * Return: Always 0.
 */
char *_strdup(char *str)
{
	char *a;
	int i;
	int j;

	if (!str)
		return (NULL);
	i = 0;
	while (str[i] != '\0')
		i++;
	a = malloc(sizeof(char) * (i + 1));
	if (a == NULL)
		return (NULL);
	for (j = 0; str[j]; j++)
		a[j] = str[j];
	return (a);
}
/**
 * _strchr - entry point
 * @s: input
 * @c: input
 * Return: Always 0 (Success)
 */
char *_strchr(char *s, char c)
{
        int i = 0;

        for (; s[i] >= '\0'; i++)
        {
                if (s[i] == c)
                        return (&s[i]);
        }
        return (0);
}