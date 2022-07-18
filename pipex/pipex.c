/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwallier <rwallier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 17:27:45 by rwallier          #+#    #+#             */
/*   Updated: 2022/07/17 06:48:02 by rwallier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	close_pipes_all(int **fd, int inpipe, int outpipe);

int	main(int argc, char *argv[], char **env)
{
	int	proccess_id;
	int	file[2];
	int	**fd;
	int	index;

	initial_errors(fd, argc, file, argv);
	index = 0;
	while (index < (argc - 3))
	{
		proccess_id = fork();
		fork_error(proccess_id);
		if (proccess_id == 0)
		{
			if (index + 2 == 2)
			{
				// close_pipes(fd, -1, index);
				printf("%i\n", file[0]);
				close(fd[0][0]);
				close(fd[1][0]);
				close(fd[1][1]);
				close(fd[2][0]);
				run_commands(file[0], fd[0][1], argv[index + 2], env);
			}
			else if (index + 2 == argc - 2)
			{
				// close_pipes(fd, index, -1);
				close(fd[0][1]);
				close(fd[1][0]);
				close(fd[1][1]);
				run_commands(fd[0][0], file[1], argv[argc - 2], env);
			}
			// else
			// {
			// 	close_pipes(fd, index, index + 1);
			// 	run_commands(fd[index][0], fd[index + 1][1], argv[index + 2], env);
			// }
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

