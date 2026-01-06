#include "shell.h"

/**
 * get_env_value - get environment value by name
 * @name: variable name (ex: "PATH")
 *
 * Return: pointer to value inside environ or NULL
 */
char *get_env_value(const char *name)
{
	size_t i, nlen;

	if (!name || !environ)
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
 * Return: malloc'd string or NULL
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
 * resolve_command - resolve cmd using PATH, with edge cases:
 * - if cmd has '/', treat as path
 * - if PATH missing, use default "/bin:/usr/bin"
 * - empty PATH elements mean current directory "."
 * @cmd: command (argv[0])
 *
 * Return: malloc'd resolved path or NULL if not found
 */
char *resolve_command(char *cmd)
{
	char *path, *copy, *start, *end, *full;

	if (!cmd || cmd[0] == '\0')
		return (NULL);

	if (strchr(cmd, '/'))
	{
		if (access(cmd, X_OK) == 0)
			return (strdup(cmd));
		return (NULL);
	}

	path = get_env_value("PATH");
	if (!path)
		path = "/bin:/usr/bin";

	copy = strdup(path);
	if (!copy)
		return (NULL);

	start = copy;
	while (1)
	{
		end = strchr(start, ':');
		if (end)
			*end = '\0';

		if (*start == '\0')
			full = build_path(".", cmd);
		else
			full = build_path(start, cmd);

		if (full && access(full, X_OK) == 0)
		{
			free(copy);
			return (full);
		}

		free(full);

		if (!end)
			break;

		start = end + 1;
	}

	free(copy);
	return (NULL);
}
