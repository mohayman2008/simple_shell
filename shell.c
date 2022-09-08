#include "hsh.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>

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
	char **args = NULL;
	unsigned char exit = 0;
	int exec_status __attribute__((unused));
	ssize_t read_count = 0;
/*	struct stat statbuf;*/

	while (!exit)
	{
/*		printf("%s", prompt_str);*/
		write(STDOUT_FILENO, prompt_str, 10);
		args = read_prompt(&read_count);

		if (read_count < 0 || !args || !*args)
		{
			free_str_array(args);
			break;
		}
/*		if (!stat(args[0], &statbuf))*/
/*		{*/
			exec_status = exec(args[0], args, environ);
			if (exec_status < 0)
				perror(av[0]);
/*		}*/
/*		else*/
			/*	fprintf(stdout, "%s: No such file or directory\n", av[0]);*/
		free_str_array(args);
	}
	return (0);
}
