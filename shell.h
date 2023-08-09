#ifndef SHELL_H
#define SHELL_H

/* Libraries */
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <limit.h>
#include <fcntl.h>
#include <errno.h>

/* Macros */
#define BUFFER_SIZE 1024

/* string functions 
 * 0-strings.c */
int _strlen(char *s);
void _puts(char *str);
char *_strcpy(char *dest, char *src);
int _putchar(char c);
int _strcmp(char *s1, char *s2);

/* 1-strings.c */
char *_strdup(char *str);
char *_strchr(char *s, char c);

/*memory.c*/
char *__memcpy(char *dest, char *src, unsigned int n);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
