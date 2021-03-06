/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwallier <rwallier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 15:07:46 by rwallier          #+#    #+#             */
/*   Updated: 2022/07/22 21:52:10 by rwallier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <errno.h>
# include "libft.h"

void	initial_errors(int argc, int file[2], char *argv[], int fd[2]);

int		first_comand(int argc, char *argv[], int file[2], int fd[2]);

int		last_command(int argc, char *argv[], int file[2], int fd[2]);

char	*get_path(void);

char	**get_arguments(char *argv);

char	*find_path(char *command, char **env);

int		run_commands(int infile, int outfile, char *cmds, char **env);

void	close_pipes(int used_pipe, int argc, int **fd);

void	close_first_pipes(int used_pipe, int argc, int **fd);

void	close_last_pipes(int used_pipe, int argc, int **fd);

void	broken_pipe(void);

void	wrong_path(void);

void	usage_error(void);

void	open_error(void);

void	wait_error(void);

void	fork_error(int proccess_id);

#endif
