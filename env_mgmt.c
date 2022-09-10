#include "hsh.h"
#include <string.h>

/**
 * _setenv - changes or adds an environment variable
 * @name: variable name
 * @value: the new value
 * @overwrite: overwriting flag, (0) for not overwriting and overwrite if
 *		any other value
 *
 * Return: 0 on success or -1 on error
 */
int _setenv(const char *name, const char *value, int overwrite)
{
	char **var_ptr, *new_var, **new_env;
	int len = 0;

	if (!name || !*name || !value)
		return (-1);

	var_ptr = _getenv_ptr(name);
	if (var_ptr && *var_ptr && !overwrite)
		return (0);

	new_var = malloc(sizeof(*new_var) * (strlen(name) + strlen(value) + 2));
	if (!new_var)
		perror("Memmory error"), exit(98);

	strcpy(new_var, name);
	strcat(new_var, "=");
	strcat(new_var, value);

	if (var_ptr && overwrite)
	{
		free(*var_ptr);
		*var_ptr = new_var;
	}
	else
	{
		while (environ[len])
			len++;

		new_env = realloc(environ, sizeof(*environ) * (len + 2));
		if (!new_env)
			free(environ), perror("Memmory error"), exit(98);

		environ = new_env;
		environ[len] = new_var;
		environ[len + 1] = NULL;
	}
	return (0);
}

/**
 * _unsetenv - deletes an environment variable
 * @name: variable name
 *
 * Return: 0 on success or -1 on error
 */
int _unsetenv(const char *name)
{
	char **var_ptr, **new_env;
	int len = 0;

	if (!name || !*name)
		return (-1);

	var_ptr = _getenv_ptr(name);
	if (var_ptr && *var_ptr)
	{
		free(*var_ptr);

		while (*var_ptr)
		{
			*var_ptr = *(var_ptr + 1);
			var_ptr++;
		}

		while (environ[len])
			len++;

		new_env = realloc(environ, sizeof(*environ) * (len + 1));
		if (!new_env)
			perror("Memmory error");
		else
			environ = new_env;

		return (0);
	}

	return (-1);
}
