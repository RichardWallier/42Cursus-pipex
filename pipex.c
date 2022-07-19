/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwallier <rwallier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 17:27:45 by rwallier          #+#    #+#             */
/*   Updated: 2022/07/18 22:53:36 by rwallier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"


void	close_pipes_all(int **fd, int inpipe, int outpipe);

int	main(int argc, char *argv[], char **env)
{
	int	proccess_id[argc - 3];
	int	file[2];
	int	fd[argc - 4][2];
	int	index;

	initial_errors(argc, file, argv, fd);
	index = 0;
	proccess_id[index] = first_comand(argc, argv, file, fd);
	while (index < (argc - 5))
	{
		proccess_id[index + 1] = fork();
		if (proccess_id[index + 1] == 0)
		{
			close_pipes(index, argc, fd);
			run_commands(fd[index][0], fd[index + 1][1], argv[index + 3], env);
		}
		index++;
	}
	last_command(argc, argv, file, fd);
	close_pipes(-1, argc, fd);
	wait(proccess_id);
	return (0);
}

int	first_comand(int argc, char *argv[], int file[2], int fd[argc - 4][2])
{
	extern char	**environ;
	int	proccess_id;
	int	status;

	status = 0;
	proccess_id = fork();
	if (proccess_id == 0)
	{
		close_first_pipes(0, argc, fd);
		run_commands(file[0], fd[0][1], argv[2], environ);
	}
	return (proccess_id);
}

int	last_command(int argc, char *argv[], int file[2], int fd[argc - 4][2])
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

void wait_error(void)
{
	ft_printf("wait error\n");
}
