#include "main.h"

extern char **environ;

int main(int argc, char **argv, char **envp)
{
	char *line;
	char *token;
	size_t i;
	int j = 0, a = 0;
	char **arr;
	int status;
	pid_t pid;

	(void)argc;
	(void)argv;
	(void)envp;

	while (1)
	{
		if (isatty(STDIN_FILENO))
		write(1, "$ ", 2);

		j = getline(&line, &i, stdin);
		if (j == -1)
		{
			write(1, "\n", 1);
			break;
		}

		token = strtok(line, " \n\t");
		arr = malloc(sizeof(char *) * 1024);

		while (token != NULL)
		{
			arr[a] = token;
			token = strtok(NULL, " \n\t");
			a++;
		}
		arr[a] = token;
		
		pid = fork();
		if (pid == 0)
		{
			execve(line, arr, environ);
		}
		else
		{
			wait(&status);
		}
	}
	free(line);
	free(arr);

	return (0);
}
