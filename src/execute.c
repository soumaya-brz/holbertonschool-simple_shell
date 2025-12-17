#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include "shell.h"

/**
 * execute - executes a command
 * @argv: argument vector
 * @env: environment
 *
 * Return: 0 on success, -1 on failure
 */
int execute(char **argv, char **env)
{
	pid_t pid;
	int status;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return (-1);
	}

	if (pid == 0)
	{
		if (execve(argv[0], argv, env) == -1)
		{
			perror(argv[0]);
			exit(1);
		}
	}
	else
	{
		wait(&status);
	}

	return (0);
}

