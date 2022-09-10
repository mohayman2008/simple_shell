#include "hsh.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

/**
 * bulitin_cmd - handle built-in commands
 * @av: input line tokens vector
 *
 * Return: 1 on matching cmd and 0 eslewisw
 */
int bulitin_cmd(char **av)
{
	char **str_itr;

	if (!strcmp(av[0], "setenv"))
	{
		if(setenv(av[1], av[2], 1) < 0)
			perror("setenv error");
		return (1);
	}
	else if (!strcmp(av[0], "unsetenv"))
	{
		if(unsetenv(av[1]) < 0)
			perror("unsetenv error");
		return (1);
	}
	else if (!strcmp(av[0], "env"))
	{
		for (str_itr = environ ; *str_itr ; str_itr++)
			printf("%s\n", *str_itr);
		return (1);
	}

	setenv("user", "mohamed", 1);
	setenv("user", "mohamedAyman", 1);
	unsetenv("USER");

	return (0);
}

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
	char **args = NULL;
	unsigned char running = 1, exit_status = EXIT_SUCCESS;
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
			if (bulitin_cmd(args))
				;
			else if (!strcmp(*args, "exit"))
				exit_status = args[1] ? atoi(args[1]) & 0xFF : exit_status,
					free_str_array(args),
					exit(exit_status);
			else
			{
				exit_status = exec(args[0], args, environ);
				if (exit_status)
					perror(av[0]);
			}
		}
		free_str_array(args);
	}
	return (0);
}
