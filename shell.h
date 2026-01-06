#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <errno.h>

#define PROMPT "$ "
#define DELIMS " \t\r\n"

extern char **environ;

/* main loop */
int shell_loop(char *progname);

/* tokenizer */
int count_words(char *line);
char **split_line(char *line);

/* path */
char *get_env_value(const char *name);
char *build_path(const char *dir, const char *cmd);
char *resolve_command(char *cmd);

/* execute & builtins */
int handle_builtin(char **argv, char *line);
int execute_command(char **argv, char *progname, unsigned long cmd_count);
void print_not_found(char *progname, unsigned long cmd_count, char *cmd);
void print_env(void);

#endif
