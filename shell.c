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
	int exit_status = EXIT_SUCCESS;
	ssize_t read_count = 0;

	while (ac == 1 && running)
	{
		if (isatty(STDIN_FILENO))
			printf("%s", prompt_str);
		args = read_prompt(&read_count);

		if (read_count < 0)
			running = 0;
		else if (args && *args)
		{
			if (strcmp(*args, "exit") == 0)
				exit_status = args[1] ? atoi(args[1]) & 0xFF : exit_status,
				free_str_array(args),
				exit(exit_status);
			else if (strcmp(*args, "env") == 0)
			{
				for (str_itr = environ ; *str_itr ; str_itr++)
					printf("%s\n", *str_itr);
			}
			else
			{
				exit_status = exec(args[0], args, environ);
				if (exit_status < 0)
					perror(av[0]);
			}
		}
		free_str_array(args);
	}
	return (0);
}
