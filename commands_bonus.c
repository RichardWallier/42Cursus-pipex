#include "pipex_bonus.h"

void	middle_commands(int argc, int **fd, char *argv[], char **env)
{
	int	index;
	int	proccess_id;

	index = 0;
	while (index < (argc - 5))
	{
		proccess_id = fork();
		if (proccess_id == 0)
		{
			close_pipes(index, argc, fd);
			run_commands(fd[index][0], fd[index + 1][1], argv[index + 3], env);
		}
		index++;
	}
}

int	first_comand(int argc, char *argv[], int file[2], int **fd)
{
	extern char	**environ;
	int	proccess_id;

	proccess_id = fork();
	if (proccess_id == 0)
	{
		close_first_pipes(0, argc, fd);
		run_commands(file[0], fd[0][1], argv[2], environ);
	}
	return (proccess_id);
}

int	last_command(int argc, char *argv[], int file[2], int **fd)
{
	extern char	**environ;
	int	proccess_id;

	proccess_id = fork();
	if (proccess_id == 0)
	{
		close_last_pipes(argc - 5, argc, fd);
		run_commands(fd[argc - 5][0], file[1], argv[argc - 2], environ);
	}
	return (proccess_id);
}
