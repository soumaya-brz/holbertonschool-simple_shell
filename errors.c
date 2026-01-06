#include "shell.h"

/**
 * print_not_found - prints the required error format
 * @progname: shell name (argv[0])
 * @cmd_count: command index
 * @cmd: command not found
 */
void print_not_found(char *progname, unsigned long cmd_count, char *cmd)
{
	fprintf(stderr, "%s: %lu: %s: not found\n", progname, cmd_count, cmd);
}
