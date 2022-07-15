/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errorhandling.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwallier <rwallier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 15:00:12 by rwallier          #+#    #+#             */
/*   Updated: 2022/07/15 17:10:44 by rwallier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	broken_pipe(void)
{
	perror("Error with pipe!");
	exit(errno);
}

void	wrong_path(void)
{
	errno = ENOENT;
	perror("Error with command!");
	exit(errno);
}

void	usage_error(void)
{
	errno = EINVAL;
	perror("usage: ./pipex \"infile\" \"cmd1\" \"cmd2\" \"outfile\"");
	exit(errno);
}

void	open_error(void)
{
	perror("Error with file!");
	exit(errno);
}

void	fork_error(int procces_id)
{
	if (procces_id < 0)
	{
		perror("Error with fork!");
		exit(errno);
	}
}
