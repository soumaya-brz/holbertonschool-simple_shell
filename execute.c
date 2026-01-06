#include "shell.h"

/**
 * execute_command - resolve cmd then fork/execve/wait
 * fork MUST NOT be called if command doesn’t exist
 * @argv: tokenized argv
 * @progname: shell name (argv[0])
 * @cmd_count: command index
 *
 * Return: 0
 */
int execute_command(char **argv, char *progname, unsigned long cmd_count)
{
	char *cmd_path;
	pid_t pid;
	int status;

	cmd_path = resolve_command(argv[0]);
	if (!cmd_path)
	{
		print_not_found(progname, cmd_count, argv[0]);
		return (0);
	}

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
		perror(progname);
		free(cmd_path);
		_exit(126);
	}

	waitpid(pid, &status, 0);
	free(cmd_path);
	return (0);
}
