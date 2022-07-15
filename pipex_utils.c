/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwallier <rwallier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 17:01:03 by rwallier          #+#    #+#             */
/*   Updated: 2022/07/15 17:09:59 by rwallier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	initial_errors(int fd[2], int argc, int file[2])
{
	if (pipe(fd) == -1)
		broken_pipe();
	if (argc != 5)
		usage_error();
	if (file[0] < 0 || file[1] < 0)
		open_error();
}

void	close_pipe(int fd[2])
{
	close(fd[0]);
	close(fd[1]);
}

char	*find_path(char *command, char **env)
{
	char	**path;
	char	*command_path;
	char	*temp;
	int		index;

	index = 0;
	while (env[index])
	{
		if (strncmp("PATH=", env[index], 5) == 0)
			path = ft_split(&env[index][5], ':');
		index++;
	}
	index = 0;
	while (path[index])
	{
		temp = ft_strjoin(path[index], "/");
		free(path[index++]);
		command_path = ft_strjoin(temp, command);
		free(temp);
		if (access(command_path, F_OK | X_OK) == 0)
			return (command_path);
		free(command_path);
	}
	wrong_path();
	return (NULL);
}

int	run_commands(int infile, int outfile, char *cmds, char **env)
{
	char	*path;
	char	**arguments;

	arguments = get_arguments(cmds);
	path = find_path(arguments[0], env);
	dup2(infile, STDIN_FILENO);
	close(infile);
	dup2(outfile, STDOUT_FILENO);
	close(outfile);
	if (execve(path, arguments, NULL) == -1)
		wrong_path();
	return (1);
}

char	**get_arguments(char *argv)
{
	char	**args;
	char	*temp;
	char	**trimmed;
	int		index;

	args = ft_split2(argv, ' ');
	index = 0;
	while (args[index])
		index++;
	trimmed = (char **)malloc(index * sizeof(char *));
	index = 0;
	while (args[index])
	{
		trimmed[index] = ft_strtrim(args[index], "'\"");
		free(args[index]);
		index++;
	}
	free(args);
	return (trimmed);
}
