#include "shell.h"

int shell_loop(char *progname)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t nread;
	char **argv;
	unsigned long count = 0;
	int interactive = isatty(STDIN_FILENO);
	int last_status = 0;

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
			return (last_status);
		}

		argv = split_line(line);
		if (!argv || !argv[0])
		{
			free(argv);
			continue;
		}

		count++;

		if (is_exit(argv))
		{
			free(argv);
			free(line);
			return (last_status);
		}

		if (is_env(argv))
		{
			print_env();
			last_status = 0;
			free(argv);
			continue;
		}

		execute_command(argv, progname, count, &last_status);
		free(argv);
	}
}
