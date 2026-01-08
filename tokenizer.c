#include "shell.h"

int count_words(char *line)
{
	int count = 0, in_word = 0;
	size_t i;

	for (i = 0; line && line[i]; i++)
	{
		if (strchr(DELIMS, line[i]))
			in_word = 0;
		else if (!in_word)
		{
			in_word = 1;
			count++;
		}
	}
	return (count);
}

char **split_line(char *line)
{
	char **argv;
	char *tok;
	int words, i = 0;

	words = count_words(line);
	argv = malloc(sizeof(char *) * (words + 1));
	if (!argv)
		return (NULL);

	tok = strtok(line, DELIMS);
	while (tok)
	{
		argv[i++] = tok;
		tok = strtok(NULL, DELIMS);
	}
	argv[i] = NULL;
	return (argv);
}
