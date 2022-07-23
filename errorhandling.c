/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errorhandling.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwallier <rwallier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 15:00:12 by rwallier          #+#    #+#             */
/*   Updated: 2022/07/22 21:53:55 by rwallier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	broken_pipe(void)
{
	perror("Error with pipe!");
	exit(1);
}

void	wrong_path(void)
{
	perror("Error with command!");
	exit(1);
}

void	usage_error(void)
{
	errno = EINVAL;
	perror("usage: ./pipex infile \"cmd1\" \"cmd2\" outfile");
	exit(1);
}

void	open_error(void)
{
	perror("Error with file!");
	exit(1);
}

void	fork_error(int procces_id)
{
	if (procces_id < 0)
	{
		perror("Error with fork!");
		exit(1);
	}
}
