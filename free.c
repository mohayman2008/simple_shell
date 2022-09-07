#include "hsh.h"

/**
 * free_str_array - free dynamically allocated NULL terminated array of
 *              dynamically allocated (char *)s <strings>
 * @str_arr: arrray of (char *)s to be freed
 */
void free_str_array(char **str_arr)
{
	int i = 0;

	if (str_arr)
	{
		while (str_arr[i])
		{
			free(str_arr[i]);
			i++;
		}
		free(str_arr);
	}
}
