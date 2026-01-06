#include "shell.h"

/**
 * get_env_value - get value of environment variable name
 * @name: variable name (e.g. "PATH")
 *
 * Return: pointer to value inside environ, or NULL
 */
char *get_env_value(const char *name)
{
	size_t i, nlen;

	if (!name)
		return (NULL);

	nlen = strlen(name);

	for (i = 0; environ[i]; i++)
	{
		if (strncmp(environ[i], name, nlen) == 0 && environ[i][nlen] == '=')
			return (environ[i] + nlen + 1);
	}
	return (NULL);
}

/**
 * build_path - build "dir/cmd"
 * @dir: directory
 * @cmd: command
 *
 * Return: malloc'd string "dir/cmd" or NULL
 */
char *build_path(const char *dir, const char *cmd)
{
	size_t dlen, clen;
	char *full;

	if (!dir || !cmd)
		return (NULL);

	dlen = strlen(dir);
	clen = strlen(cmd);

	full = malloc(dlen + 1 + clen + 1);
	if (!full)
		return (NULL);

	strcpy(full, dir);
	full[dlen] = '/';
	strcpy(full + dlen + 1, cmd);

	return (full);
}

/**
 * resolve_command - resolve command using PATH (or direct path)
 * @cmd: command name (argv[0])
 *
 * Return: malloc'd full path to execve, or NULL if not found
 */
char *resolve_command(char *cmd)
{
	char *path, *path_copy, *dir, *full;

	if (!cmd || cmd[0] == '\0')
		return (NULL);

	/* If cmd contains '/', treat as path */
	if (strchr(cmd, '/'))
	{
		if (access(cmd, X_OK) == 0)
			return (strdup(cmd));
		return (NULL);
	}

	path = get_env_value("PATH");
	if (!path)
		return (NULL);

	path_copy = strdup(path);
	if (!path_copy)
		return (NULL);

	dir = strtok(path_copy, ":");
	while (dir)
	{
		full = build_path(dir, cmd);
		if (full && access(full, X_OK) == 0)
		{
			free(path_copy);
			return (full);
		}
		free(full);
		dir = strtok(NULL, ":");
	}

	free(path_copy);
	return (NULL);
}
