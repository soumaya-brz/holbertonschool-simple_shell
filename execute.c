#include "shell.h"

/**
 * print_not_found - prints "prog: count: cmd: not found"
 * @progname: argv[0]
 * @cmd_count: command number
 * @cmd: command string
 */
void print_not_found(char *progname, unsigned long cmd_count, char *cmd)
{
	fprintf(stderr, "%s: %lu: %s: not found\n", progname, cmd_count, cmd);
}

/**
 * print_env - prints environment variables
 */
void print_env(void)
{
	size_t i;

	for (i = 0; environ[i]; i++)
	{
		write(STDOUT_FILENO, environ[i], strlen(environ[i]));
		write(STDOUT_FILENO, "\n", 1);
	}
}

/**
 * handle_builtin - handle builtins: exit, env
 * @argv: tokenized argv
 * @line: original line buffer (unused here but kept for clarity)
 *
 * Return: 1 if "exit" (caller should exit shell), 0 otherwise
 */
int handle_builtin(char **argv, char *line)
{
	(void)line;

	if (!argv || !argv[0])
		return (0);

	if (strcmp(argv[0], "exit") == 0)
		return (1);

	if (strcmp(argv[0], "env") == 0)
	{
		print_env();
		return (0);
	}

	return (0);
}

/**
 * execute_command - resolves command, forks, execve, waits
 * @argv: tokenized argv
 * @progname: argv[0] of shell
 * @cmd_count: command number (for error format)
 *
 * Return: 0 always
 */
int execute_command(char **argv, char *progname, unsigned long cmd_count)
{
	pid_t pid;
	int status;
	char *cmd_path;

	cmd_path = resolve_command(argv[0]);
	if (!cmd_path)
	{
		print_not_found(progname, cmd_count, argv[0]);
		return (0);
	}

	/* fork must NOT be called if command doesn't exist */
	pid = fork();
	if (pid == -1)
	{
		perror(progname);
		free(cmd_path);
		return (0);
	}

	if (pid == 0)
	{
		execve(cmd_path, argv, environ);
		/* If execve returns, it failed */
		perror(progname);
		free(cmd_path);
		_exit(126);
	}

	waitpid(pid, &status, 0);
	free(cmd_path);
	return (0);
}
