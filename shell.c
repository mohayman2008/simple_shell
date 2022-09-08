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
int main(int ac, char **av, char **env __attribute__((unused)))
{
	char *prompt_str = "#cisfun$ ";
	char **args = NULL, **str_itr;
	unsigned char running = 1;
	int exec_status;
	ssize_t read_count = 0;
/*	struct stat statbuf;*/

	while (ac == 1 && running)
	{
		if (isatty(STDIN_FILENO))
			printf("%s", prompt_str);
/*		write(STDOUT_FILENO, prompt_str, 10);*/
		args = read_prompt(&read_count);

		if (read_count < 0)
		{
			/*free_str_array(args);*/
			running = 0;
		}
/*		if (!stat(args[0], &statbuf))*/
		else if (args && *args)
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
