#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "shell.h"

/**
 * split_line - splits a line into tokens
 * @line: input line
 *
 * Return: array of tokens
 */
char **split_line(char *line)
{
	char **tokens;
	char *token;
	int i = 0;

	tokens = malloc(sizeof(char *) * 64);
	if (tokens == NULL)
		return (NULL);

	token = strtok(line, " \t\n");
	while (token != NULL)
	{
		tokens[i] = token;
		i++;
		token = strtok(NULL, " \t\n");
	}
	tokens[i] = NULL;

	return (tokens);
}

/**
 * main - entry point of the shell
 * @ac: argument count
 * @av: argument vector
 * @envp: environment
 *
 * Return: Always 0
 */
int main(int ac, char **av, char **envp)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t read;
	char **argv;

	(void)ac;
	(void)av;

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

		argv = split_line(line);
		if (argv == NULL || argv[0] == NULL)
		{
			free(argv);
			continue;
		}

		execute(argv, envp);
		free(argv);
	}

	free(line);
	return (0);
}
