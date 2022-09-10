#include "hsh.h"
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

/**
 * exec - forks current process and executes a program
 * @filepath: Absoulte path of the program to execute
 * @av: arguments vector
 * @env: environment vector
 *
 * Return: (-1) on failure, (1) on success
 */
int exec(char *filepath, char **av, char **env)
{
	int wstatus = 0;
	pid_t child;
	char *path;

	path = get_path(filepath);
	if (path)
	{
		child = fork();
		if (child == -1)
			return (-1);
		if (child == 0)
		{
			execve(path, av, env);
			exit(EXIT_FAILURE);
		}
		else
			wait(&wstatus);
	}
	else
		return (2);

	free(path);
	return (wstatus);
}
