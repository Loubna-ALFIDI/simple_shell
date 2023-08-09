#include "shell.h"
#include <stdlib.h>

/**
 * __memcpy - copies memory area.
 * @dest: memory area to copy to.
 * @src: memory area to copy from.
 * @n: bytes of memory.
 * Return: a pointer to dest.
 */

char *__memcpy(char *dest, char *src, unsigned int n)
{
	unsigned int i;

	i = 0;
	while (i < n)
	{
		dest[i] = src[i];
		i++;
	}
	return (dest);
}

/**
 * _realloc - reallocates a memory block using malloc and free
 * @ptr: pointer to the memory previously allocated
 * @old_size: the size, in bytes, of the allocated space for ptr
 * @new_size: the new size, in bytes of the new memory block
 * Return: pointer is worked, NULL otherwise.
 */

void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	void *pointer;

	if (old_size == new_size)
		return (ptr);
	if (!ptr)
	{
		pointer = malloc(new_size);
		if (!pointer)
			return (NULL);
		return (pointer);
	}
	if (new_size == 0 && ptr != NULL)
	{
		free(ptr);
		return (NULL);
	}
	pointer = malloc(new_size);
	if (!pointer)
		return (NULL);
	if (new_size < old_size)
	{
		__memcpy(pointer, ptr, new_size);
		free(ptr);
		return (pointer);
	}
	else
	{
		__memcpy(pointer, ptr, old_size);
		free(ptr);
		return (pointer);
	}
}
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
