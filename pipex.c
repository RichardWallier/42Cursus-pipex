/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwallier <rwallier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 17:27:45 by rwallier          #+#    #+#             */
/*   Updated: 2022/07/22 21:21:58 by rwallier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char *argv[], char **env)
{
	int	proccess_id[2];
	int	file[2];
	int	fd[2];

	initial_errors(argc, file, argv, fd);
	proccess_id[0] = fork();
	if (proccess_id[0] == 0)
	{
		close(fd[0]);
		run_commands(file[0], fd[1], argv[2], env);
	}
	proccess_id[1] = fork();
	if (proccess_id[1] == 0)
	{
		close(fd[1]);
		run_commands(fd[0], file[1], argv[3], env);
	}
	close(fd[0]);
	close(fd[1]);
	waitpid(proccess_id[0], NULL, 0);
	waitpid(proccess_id[1], NULL, 0);
	return (0);
}
