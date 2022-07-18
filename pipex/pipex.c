/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwallier <rwallier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 17:27:45 by rwallier          #+#    #+#             */
/*   Updated: 2022/07/18 15:42:18 by vsergio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	close_pipes_all(int **fd, int inpipe, int outpipe);

int	main(int argc, char *argv[], char **env)
{
	int	proccess_id;
	int	file[2];
	int	fd[argc - 4][2];
	int	index;

	initial_errors((int **)fd, argc, file, argv);
	index = 0;
	while (index < (argc - 3))
	{
		proccess_id = fork();
		fork_error(proccess_id);
		if (proccess_id == 0)
		{
			if (index + 2 == 2)
			{
				close_first_pipes((int **)fd, index);
				run_commands(file[0], fd[0][1], argv[index + 2], env);
			}
			else if (index + 2 == argc - 2)
			{
				close_last_pipes((int **)fd, index);
				run_commands(fd[index][0], file[1], argv[argc - 2], env);
			}
			else
			{
				close_pipes((int **)fd, index);
				run_commands(fd[index][0], fd[index + 1][1], argv[index + 2], env);
			}
		}
		else
			wait(&proccess_id);
		index++;
	}
	index = 0;
	// while (fd[index])
	// {
	// 	close(fd[index][0]);
	// 	perror("");
	// 	close(fd[index][1]);
	// 	perror("");
	// 	index++;
	// }
	return (0);
}

