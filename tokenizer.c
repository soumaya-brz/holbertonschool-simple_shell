#include "shell.h"

/**
 * count_words - count tokens in a line using DELIMS
 * @line: input line
 *
 * Return: number of words
 */
int count_words(char *line)
{
	int count = 0, in_word = 0;
	size_t i;

	if (!line)
		return (0);

	for (i = 0; line[i] != '\0'; i++)
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

/**
 * split_line - split line into argv array (tokens point inside line)
 * @line: input line (modified by strtok)
 *
 * Return: malloc'd argv array (must free(argv))
 */
char **split_line(char *line)
{
	char **argv;
	int words, i = 0;
	char *tok;

	if (!line)
		return (NULL);

	words = count_words(line);
	if (words == 0)
	{
		/* strtok would return NULL anyway */
		argv = malloc(sizeof(char *));
		if (!argv)
			return (NULL);
		argv[0] = NULL;
		return (argv);
	}

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
