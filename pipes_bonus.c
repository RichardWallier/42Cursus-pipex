/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwallier <rwallier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 16:55:37 by rwallier          #+#    #+#             */
/*   Updated: 2022/07/22 21:37:52 by rwallier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	close_first_pipes(int used_pipe, int argc, int **fd)
{
	int	index;

	index = 0;
	while (index < argc - 4)
	{
		if (index == used_pipe)
		{
			close(fd[index][0]);
		}
		else
		{
			close(fd[index][0]);
			close(fd[index][1]);
		}
		index++;
	}
	return ;
}

void	close_last_pipes(int used_pipe, int argc, int **fd)
{
	int	index;

	index = 0;
	while (index < argc - 4)
	{
		if (index == used_pipe)
		{
			close(fd[index][1]);
		}
		else
		{
			close(fd[index][0]);
			close(fd[index][1]);
		}
		index++;
	}
}

void	close_pipes(int used_pipe, int argc, int **fd)
{
	int	index;

	index = 0;
	while (index < argc - 4)
	{
		if (index == used_pipe)
		{
			close(fd[index][1]);
			close(fd[index + 1][0]);
			index++;
		}
		else
		{
			close(fd[index][0]);
			close(fd[index][1]);
		}
		index++;
	}
}

void	close_files(int file[2], char *argv[])
{
	if (ft_strncmp(argv[1], "here_doc", 8) == 0)
		unlink("./tempfile");
	close(file[0]);
	close(file[1]);
}
