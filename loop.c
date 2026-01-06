#include "shell.h"

/**
 * shell_loop - main loop: prompt, read, parse, execute
 * @progname: argv[0] of the shell
 *
 * Return: 0
 */
int shell_loop(char *progname)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t nread;
	char **argv;
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

		argv = split_line(line);
		if (!argv || !argv[0])
		{
			free(argv);
			continue;
		}

		cmd_count++;

		if (is_exit(argv))
		{
			free(argv);
			free(line);
			return (0);
		}

		if (is_env(argv))
		{
			print_env();
			free(argv);
			continue;
		}

		execute_command(argv, progname, cmd_count);
		free(argv);
	}
}
