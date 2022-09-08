#include "hsh.h"

/**
 * char_cmp - check if a character belongs to a set of charcters in a string
 * @c: character to compare
 * @c_set: string of the set of characters to compare with
 *
 * Return: 1 if found, 0 if not, -1 on error
 */
int char_cmp(char c, char *c_set)
{
	int i = 0;

	if (!c_set)
		return (-1);
	for (i = 0 ; c_set[i] ; i++)
	{
		if (c == c_set[i])
			return (1);
	}
	return (0);
}

/**
 * get_tokens - get tokens from a string delimited by delimiting characters
 *		and creating a NULL terminated vector of strings containg
 *		duplicates of the found tokens, the caller should free the
 *		allocated memory using free_str_array()
 * @str: input string
 * @delim: the set of the delimiting characters
 *
 * Return: the generated strings vector or NULL on errors
 */
char **get_tokens(char *str, char *delim)
{
	char **tokens = NULL, *current, **new_tokens;
	size_t size = 0, tokens_itr = 0, len = 0;

	if (!str)
		return (NULL);
	delim = !delim ? "" : delim;

	current = str;
	while (*(current + len))
	{
		if (char_cmp(*(current + len), delim) && !len)
			current++;
		else if (char_cmp(*(current + len), delim))
		{
			if (tokens_itr + 1 > size)
			{
				size += PTR_BUF_SIZE_INC;
				new_tokens = realloc(tokens, sizeof(*tokens) * (size + 1));
				if (!new_tokens)
				{
					free_str_array(tokens), perror("Getting args error");
					return (NULL);
				}
				tokens = new_tokens;
			}
			tokens[tokens_itr] = strndup(current, len);
			tokens[tokens_itr + 1] = NULL;
			if (!(tokens[tokens_itr]))
			{
				free_str_array(tokens), perror("Getting args error");
				return (NULL);
			}
			tokens_itr++, current += len + 1, len = 0;
		}
		else
			len++;
	}
	return (tokens);
}

/**
 * read_prompt - reads a line and returns a NULL terminated vector of
 *		the string tokens in it
 * @read_count: Buffer to store the return value of getline()
 *
 * Return: the vector of the tokens or NULL on error
 */
char **read_prompt(ssize_t *read_count)
{
	char **args = NULL, *buf = NULL;
	size_t size = 0;

	*read_count = getline(&buf, &size, stdin);
	if (*read_count >= 0)
		args = get_tokens(buf, DELIM);

	if (buf)
		free(buf);
	return (args);
}
