#include "shell.h"

/**
 * _strdup - same work as strdup.
 * @str: string to be duplicated.
 * Return: string copy.
 */
char *_strdup(char *str)
{
	char *a = NULL;
	int i = 0;

	if (!str)
		return (NULL);
	a = malloc(sizeof(char ) * (_strlen(str) + 1));
	if (a == NULL)
		return (NULL);
	while (str[i] != '\0')
	{
		a[i] = str[i];
		i++;
	}
	a[i] = '\0';
	return (a);
}

/**
 * _strchr - same work as strchr.
 * @s: string.
 * @c: character
 * Return: pointer to first occurence of character.
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

/**
 *_strcat - same work as strcat.
 *@dest: first string.
 *@src: second string.
 *Return: concatenated string.
 */
char *_strcat(char *dest, char *src)
{
	int j, i = 0;

	while (dest[i] != '\0')
		i++;
	j = 0;
	while (src[j] != '\0')
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	dest[i] = '\0';
	return (dest);
}
