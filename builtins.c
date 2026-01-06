#include "shell.h"

/**
 * is_exit - check "exit" builtin
 * @argv: tokenized argv
 *
 * Return: 1 if exit, else 0
 */
int is_exit(char **argv)
{
	if (argv && argv[0] && strcmp(argv[0], "exit") == 0)
		return (1);
	return (0);
}

/**
 * is_env - check "env" builtin
 * @argv: tokenized argv
 *
 * Return: 1 if env, else 0
 */
int is_env(char **argv)
{
	if (argv && argv[0] && strcmp(argv[0], "env") == 0)
		return (1);
	return (0);
}

/**
 * print_env - print environment variables (safe if environ is NULL)
 */
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
