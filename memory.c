#include "shell.h"

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
 * @size: the size, in bytes, of the allocated space for ptr
 * Return: pointer is worked, NULL otherwise.
 */

void *_realloc(void *ptr, unsigned int size)
{
	void *pointer;

	if (size == 0)
	{
		free(ptr);
		return (NULL);
	}

	pointer = malloc(size);
	if (pointer == NULL)
		return (NULL);

	if (ptr != NULL)
	{
		__memcpy(pointer, ptr, size);
		free(ptr);
	}

	return (pointer);
}
