#include "shell.h"

/**
 * shell_loop - main read/execute loop
 * @progname: argv[0]
 *
 * Return: 0 on exit
 */
int shell_loop(char *progname)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t nread;
	char **args;
	unsigned long cmd_count = 0;
	int interactive = isatty(STDIN_FILENO);

	while (1)
	{
		if (interactive)
			write(STDOUT_FILENO, PROMPT, 2);

		nread = getline(&line, &len, stdin);
		if (nread == -1)
		{
			if (interactive)
				write(STDOUT_FILENO, "\n", 1);
			free(line);
			return (0);
		}

		/* Skip empty line */
		if (nread == 1)
			continue;

		args = split_line(line);
		if (!args || !args[0])
		{
			free(args);
			continue;
		}

		cmd_count++;

		/* Builtins: exit, env */
		if (handle_builtin(args, line))
		{
			free(args);
			free(line);
			return (0);
		}

		execute_command(args, progname, cmd_count);
		free(args);
	}
}
