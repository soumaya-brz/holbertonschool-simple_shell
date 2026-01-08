#include "shell.h"

int is_exit(char **argv)
{
	return (argv && argv[0] && strcmp(argv[0], "exit") == 0);
}

int is_env(char **argv)
{
	return (argv && argv[0] && strcmp(argv[0], "env") == 0);
}

void print_env(void)
{
	size_t i;

	if (!environ)
		return;

	for (i = 0; environ[i]; i++)
	{
		write(STDOUT_FILENO, environ[i], strlen(environ[i]));
		write(STDOUT_FILENO, "\n", 1);
	}
}
