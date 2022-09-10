#include "hsh.h"
#include <string.h>

/**
 * duplicate_env - create runtime duplicate of the enviroment vector and
 *		assign it to the global variable environ
 */
void duplicate_env(void)
{
	char **new_env;
	size_t len = 0, i;

	while (environ[len])
		len++;

	new_env = malloc(sizeof(*new_env) * (len + 1));
	if (!new_env)
	{
		perror("Memory error");
		return;
	}

	memcpy(new_env, environ, sizeof(*environ) * (len + 1));

	for (i = 0 ; i < len ; i++)
	{
		new_env[i] = strdup(environ[i]);
		if (!new_env[i])
		{
			free_str_array(new_env);
			perror("Memory error");
			return;
		}
	}
	environ = new_env;
}

/**
 * _getenv - get an enviroment variable
 * @key: variable name
 *
 * Return: The address of the variable string if it exists or NULL elsewise
 */
char *_getenv(const char *key)
{
	int i = 0, j;

	while (environ[i])
	{
		j = 0;
		while (environ[i][j] && environ[i][j] != '=')
		{
			if (!key[j] || environ[i][j] != key[j])
				break;
			j++;
		}
		if (!key[j] && environ[i][j] == '=')
			return (environ[i] + j + 1);
		i++;
	}

	return (NULL);
}

/**
 * _getenv_ptr - get an enviroment variable ptr in the environ vector
 * @key: variable name
 *
 * Return: The pointer to the environment variable if it exists
 *		or NULL elsewise
 */
char **_getenv_ptr(const char *key)
{
	int i = 0, j;

	if (!key || !*key)
		return (NULL);

	while (environ[i])
	{
		j = 0;
		while (environ[i][j] && environ[i][j] != '=')
		{
			if (!key[j] || environ[i][j] != key[j])
				break;
			j++;
		}
		if (!key[j] && environ[i][j] == '=')
			return (environ + i);
		i++;
	}

	return (NULL);
}
