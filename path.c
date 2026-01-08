#include "shell.h"

char *get_env_value(const char *name)
{
	size_t i, n;

	if (!name || !environ)
		return (NULL);

	n = strlen(name);
	for (i = 0; environ[i]; i++)
	{
		if (strncmp(environ[i], name, n) == 0 &&
		    environ[i][n] == '=')
			return (environ[i] + n + 1);
	}
	return (NULL);
}

char *build_path(const char *dir, const char *cmd)
{
	char *full;
	size_t d = strlen(dir), c = strlen(cmd);

	full = malloc(d + c + 2);
	if (!full)
		return (NULL);

	strcpy(full, dir);
	full[d] = '/';
	strcpy(full + d + 1, cmd);
	return (full);
}

char *resolve_command(char *cmd)
{
	char *path, *copy, *start, *end, *full;

	if (!cmd || !cmd[0])
		return (NULL);

	if (strchr(cmd, '/'))
		return (access(cmd, X_OK) == 0 ? strdup(cmd) : NULL);

	path = get_env_value("PATH");
	if (!path)
		return (NULL);

	copy = strdup(path);
	if (!copy)
		return (NULL);

	start = copy;
	while (1)
	{
		end = strchr(start, ':');
		if (end)
			*end = '\0';

		full = (*start == '\0') ?
			build_path(".", cmd) : build_path(start, cmd);

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
