#include "hsh.h"
#include <string.h>

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
 * build_path_list - creates a linked list of the paths in the PATH enviroment
 *			variable
 * Return: pointer to the head of the list or NULL on error
 */
path_t *build_path_list(void)
{
	char **path;
	int i = 0;
	path_t *path_list = NULL, *new, *last = NULL;

	path = get_tokens(_getenv("PATH"), ":");
	if (!path)
	{
		perror("Error getting PATH");
		return (NULL);
	}

	while (path[i])
	{
		new = malloc(sizeof(path_t));
		if (!new)
		{
			perror("Error creating PATH list");
			free_str_array(path), free_path_list(&path_list);
			return (NULL);
		}

		new->path = strdup(path[i]);
		if (!(new->path))
		{
			perror("Error creating PATH list");
			free_str_array(path), free_path_list(&path_list);
			return (NULL);
		}

		if (!last)
			new->next = path_list, path_list = new;
		else
			new->next = last->next, last->next = new;
		last = new;
		i++;
	}

	free_str_array(path);
	return (path_list);
}

/**
 * free_path_list - frees a pathes linked list
 * @path_list: pointer to the head of the list
 */
void free_path_list(path_t **path_list)
{
	path_t *current, *next;

	if (!path_list)
		return;

	current = *path_list;
	while (current)
	{
		next = current->next;
		free(current->path);
		free(current);
		current = next;
	}

	*path_list = NULL;
}

/**
 * search_path - find a file in the directories in the PATH enviroment variable
 * @name: file name
 *
 * Return: Absolute path of the file if found or NULL elsewise
 */
char *search_path(char *name)
{
	path_t *list, *itr;
	char *buf = NULL, *new_buf;
	size_t buf_len = 0, buf_len_inc = 128, name_len;
	struct stat stat_buf;

	if (!name || !*name)
		return (error_null("Invalid filename"));
	list = build_path_list();
	if (!list)
		return (error_null("Error creating PATH list"));
	itr = list, name_len = strlen(name);
	while (itr)
	{
		if ((strlen(itr->path) + name_len) > buf_len)
		{
			buf_len += buf_len_inc;
			new_buf = realloc(buf, sizeof(*buf) * (buf_len + 2));
			if (!new_buf)
			{
				if (buf)
					free(buf);
				free_path_list(&list);
				return (error_null("Error searching PATH"));
			}
			buf = new_buf;
		}
		strcpy(buf, itr->path), strcat(buf, "/"), strcat(buf, name);

		if (!stat(buf, &stat_buf))
		{
			free_path_list(&list);
			return (buf);
		}
		itr = itr->next;
	}

	free_path_list(&list);
/*	return ("/bin/ls");*/
	return (NULL);
}

/**
 * get_path - find a file in the directories in the PATH enviroment variable
 *		if the file name starts with '.' it will look for it in the
 *		current working directory first
 * @name: file name
 *
 * Return: path of the file if found or NULL elsewise
 */
char *get_path(char *name)
{
	char *path = NULL;
	struct stat statbuf;

	if (!name || !*name)
		return (error_null("Invalid filename"));
	if (char_cmp(name[0], "./~"))
	{
		if (!stat(name, &statbuf))
		{
			path = strdup(name);
			if (!path)
				return (error_null("Getting path error"));
		}
		else
			return (NULL);
	}
	else
	{
		path = search_path(name);
		if (!path)
			return (NULL);
	}

	return (path);
}
