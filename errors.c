#include "hsh.h"

/**
 * error_null - prints error message and returns NULL pointer
 * @error_prefix: error header
 *
 * Return: NULL pointer
 */
void *error_null(const char *error_prefix)
{
	perror(error_prefix);
	return (NULL);
}
