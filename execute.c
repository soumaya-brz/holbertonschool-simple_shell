#include "shell.h"

int execute_command(char **argv, char *progname,
		    unsigned long count, int *last_status)
{
	char *path;
	pid_t pid;
	int status;
	char *empty_env[] = { NULL };
	char **envp = environ ? environ : empty_env;

	path = resolve_command(argv[0]);
	if (!path)
	{
		print_not_found(progname, count, argv[0]);
		*last_status = 127;
		return (0);
	}

	pid = fork();
	if (pid == -1)
	{
		perror(progname);
		free(path);
		*last_status = 1;
		return (0);
	}

	if (pid == 0)
	{
		execve(path, argv, envp);
		perror(progname);
		free(path);
		_exit(126);
	}

	waitpid(pid, &status, 0);
	free(path);

	if (WIFEXITED(status))
		*last_status = WEXITSTATUS(status);
	else
		*last_status = 1;

	return (0);
}
