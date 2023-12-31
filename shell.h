#ifndef SHELL_H
#define SHELL_H

/* Libraries */
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/stat.h>

/* Macros */
#define BUFFER_SIZE 1024

/* 0-strings.c */
int _strlen(char *s);
void _puts(char *str);
char *_strcpy(char *dest, char *src);
int _putchar(char c);
int _strcmp(char *s1, char *s2);

/* 1-strings.c */
char *_strcat(char *dest, char *src);
char *_strdup(char *str);
char *_strchr(char *s, char c);

/* memory.c*/
char *__memcpy(char *dest, char *src, unsigned int n);
void *_realloc(void *ptr, unsigned int size);

/* path.c */
void execute_command(char **argv);
char *get_path(char *command);
char *_getenv(char *name);

/*builtin*/
void builtin_env(void);

/* handle.c */
void echo (char *cmd);
/*function*/
void reverse(char str[], int length);
char *_itoa(int num, char* str, int base);
int my_atoi(const char *str);

/*getline*/
ssize_t my_getline(char **lineptr, size_t *n, FILE *stream);

/*exit*/
void handle_exit(char **argv, int argc);

/* hsh.c */
char **split_input(char cmd[], int *argc);
void sigint_handler(int signum);
void non_interactive(void);
void free_argv(char **argv, int argc);

extern char **environ;

#endif
