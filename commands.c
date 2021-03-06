/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwallier <rwallier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 16:53:39 by rwallier          #+#    #+#             */
/*   Updated: 2022/07/22 16:53:41 by rwallier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	first_comand(int argc, char *argv[], int file[2], int fd[2])
{
	extern char	**environ;
	int			proccess_id;

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
	int			proccess_id;

	proccess_id = fork();
	if (proccess_id == 0)
	{
		close_last_pipes(argc - 5, argc, fd);
		run_commands(fd[argc - 5][0], file[1], argv[argc - 2], environ);
	}
	return (proccess_id);
}
