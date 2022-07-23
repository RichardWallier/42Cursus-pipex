/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwallier <rwallier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 16:54:07 by rwallier          #+#    #+#             */
/*   Updated: 2022/07/22 21:15:57 by rwallier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	middle_commands(int argc, int **fd, char *argv[], char **env)
{
	int	index;
	int	argv_index;
	int	proccess_id;
	int	cmd_num;

	index = 0;
	if (ft_strncmp(argv[1], "here_doc", 8) == 0)
	{
		cmd_num = argc - 6;
		argv_index = 1;
	}
	else
	{
		cmd_num = argc - 5;
		argv_index = 0;
	}
	while (index < cmd_num)
	{
		proccess_id = fork();
		if (proccess_id == 0)
		{
			close_pipes(index, argc, fd);
			run_commands(fd[index][0], fd[index + 1][1], argv[argv_index + 3], env);
		}
		index++;
		argv_index++;
	}
}

int	first_comand(int argc, char *argv[], int file[2], int **fd)
{
	extern char	**environ;
	int			proccess_id;
	int			argv_index;

	proccess_id = fork();
	if (ft_strncmp(argv[1], "here_doc", 8) == 0)
		argv_index = 3;
	else
		argv_index = 2;
	if (proccess_id == 0)
	{
		close_first_pipes(0, argc, fd);
		run_commands(file[0], fd[0][1], argv[argv_index], environ);
	}
	return (proccess_id);
}

int	last_command(int argc, char *argv[], int file[2], int **fd)
{
	extern char	**environ;
	int			proccess_id;
	int			pipe_index;

	if (ft_strncmp(argv[1], "here_doc", 8) == 0)
		pipe_index = argc - 6;
	else
		pipe_index = argc - 5;
	proccess_id = fork();
	if (proccess_id == 0)
	{
		close_last_pipes(pipe_index, argc, fd);
		run_commands(fd[pipe_index][0], file[1], argv[argc - 2], environ);
	}
	return (proccess_id);
}
