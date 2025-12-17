#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t read;

	while (1)
	{
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, "($) ", 4);

		read = getline(&line, &len, stdin);

		if (read == -1)
		{
			write(STDOUT_FILENO, "\n", 1);
			break;
		}
	}

	free(line);
	return (0);
}
