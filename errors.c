#include "shell.h"

void print_not_found(char *progname, unsigned long count, char *cmd)
{
	fprintf(stderr, "%s: %lu: %s: not found\n", progname, count, cmd);
}
