#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

#define PROMPT "$ "
#define DELIMS " \t\r\n"

extern char **environ;

/* loop */
int shell_loop(char *progname);

/* tokenizer */
int count_words(char *line);
char **split_line(char *line);

/* builtins */
int is_exit(char **argv);
int is_env(char **argv);
void print_env(void);

/* path */
char *get_env_value(const char *name);
char *build_path(const char *dir, const char *cmd);
char *resolve_command(char *cmd);

/* execute */
void print_not_found(char *progname, unsigned long count, char *cmd);
int execute_command(char **argv, char *progname,
		    unsigned long count, int *last_status);

#endif







