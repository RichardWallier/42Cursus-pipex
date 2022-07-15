/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwallier <rwallier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 17:27:45 by rwallier          #+#    #+#             */
/*   Updated: 2022/07/15 17:27:51 by rwallier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char *argv[], char **env)
{
	int	proccess_id;
	int	file[2];
	int	fd[2];

	file[0] = open(argv[1], O_RDONLY);
	file[1] = open(argv[4], O_WRONLY);
	initial_errors(fd, argc, file);
	proccess_id = fork();
	fork_error(proccess_id);
	if (proccess_id == 0)
	{
		close(fd[0]);
		run_commands(file[0], fd[1], argv[2], env);
	}
	wait(&proccess_id);
	proccess_id = fork();
	fork_error(proccess_id);
	if (proccess_id == 0)
	{
		close(fd[1]);
		run_commands(fd[0], file[1], argv[3], env);
	}
	close_pipe(fd);
	return (0);
}
