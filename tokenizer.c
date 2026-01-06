#include "shell.h"

/**
 * count_words - counts tokens separated by DELIMS
 * @line: input line (modified by strtok elsewhere, so only use before split)
 *
 * Return: number of words
 */
int count_words(char *line)
{
	int count = 0;
	int in_word = 0;
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
 * split_line - splits line into argv (tokens point inside line buffer)
 * @line: input line (will be modified by strtok)
 *
 * Return: NULL-terminated array of tokens (malloc'd)
 */
char **split_line(char *line)
{
	char **argv;
	int words, i = 0;
	char *tok;

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
