/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwallier <rwallier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 15:07:46 by rwallier          #+#    #+#             */
/*   Updated: 2022/07/18 15:36:39 by vsergio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <string.h>
# include <sys/wait.h>
# include <errno.h>
# include "libft/libft.h"

char	*get_path(void);
char	**get_arguments(char *argv);
void	usage_error(void);
int		run_commands(int infile, int outfile, char *cmds, char **env);
char	*find_path(char *command, char **env);
void	broken_pipe(void);
void	wrong_path(void);
void	close_pipes(int **fd, int used_pipe);
void	close_first_pipes(int **fd, int used_pipe);
void	close_last_pipes(int **fd, int used_pipe);
void	open_error(void);
void	initial_errors(int **fd, int argc, int file[2], char *argv[]);
void	fork_error(int proccess_id);

#endif
