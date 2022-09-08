#include "hsh.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

/**
 * main - simple shell
 * @ac: arguments count
 * @av: arguments vector
 * @env: environment vector
 *
 * Return: Always (0)
 */
int main(int ac __attribute__((unused)), char **av __attribute__((unused)),
	char **env __attribute__((unused)))
{
	char *prompt_str = "#cisfun$ ";
	char **args = NULL, **str_itr;
	unsigned char running = 1;

	int exec_status __attribute__((unused));
	ssize_t read_count = 0;
/*	struct stat statbuf;*/

	while (running)
	{
		printf("%s", prompt_str);
/*		write(STDOUT_FILENO, prompt_str, 10);*/
		args = read_prompt(&read_count);

		if (read_count < 0)
		{
			free_str_array(args);
			break;
		}
/*		if (!stat(args[0], &statbuf))*/
		if (args && *args)
		{
			if (strcmp(*args, "exit") == 0)
				running = 0;
			else if (strcmp(*args, "env") == 0)
			{
				for (str_itr = environ ; *str_itr ; str_itr++)
					printf("%s\n", *str_itr);
			}
			else
			{
				exec_status = exec(args[0], args, environ);
				if (exec_status < 0)
					perror(av[0]);
			}
		}
		free_str_array(args);
	}
	return (0);
}
