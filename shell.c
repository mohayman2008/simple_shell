#include "hsh.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

/**
 * main - simple shell
 * @ac: arguments count
 * @av: arguments vector
 * @env: environment vector
 *
 * Return: Always (0)
 */
int main(int ac __attribute__((unused)), char **av, char **env)
{
	char *prompt_str = "#cisfun$ ";
	char **args = NULL;
	unsigned char exit = 0;
        int exec_status __attribute__((unused));
	struct stat statbuf;

	while (!exit)
	{
		printf("%s", prompt_str);
		args = read_prompt();

		if (!args || !*args)
			break;
		if (!stat(args[0], &statbuf))
			exec_status = exec(args[0], args, env);
		else
			fprintf(stderr, "%s: No such file or directory\n", av[0]);
	}

	free_str_array(args);
	return (0);
}
