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
	int wstatus, exec_status;
	pid_t child;

	child = fork();
	if (child == -1)
		return (-1);
	if (child == 0)
	{
		exec_status = execve(filepath, av, env);
		return (exec_status);
	}
	else
		wait(&wstatus);

	return (1);
}
