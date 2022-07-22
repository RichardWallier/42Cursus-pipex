/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwallier <rwallier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 17:27:45 by rwallier          #+#    #+#             */
/*   Updated: 2022/07/22 10:44:40 by rwallier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	main(int argc, char *argv[], char **env)
{
	int	*proccess_id;
	int	file[2];
	int	**fd;
	int	index;

	fd = (int **)malloc((argc - 3) * (sizeof(int *)));
	index = 0;
	while (index < argc - 3)
		fd[index++] = (int *)malloc(2 * sizeof(int));
	proccess_id = malloc(2 * sizeof(int));
	initial_errors(argc, file, argv, fd);
	first_comand(argc, argv, file, fd);
	middle_commands(argc, fd, argv, env);
	last_command(argc, argv, file, fd);
	close_pipes(-1, argc, fd);
	index = 0;
	while (index < argc - 3)
		free(fd[index++]);
	free(fd);
	wait(NULL);
	free(proccess_id);
	return (0);
}
