/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwallier <rwallier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 17:01:03 by rwallier          #+#    #+#             */
/*   Updated: 2022/07/20 15:50:48 by rwallier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	initial_errors(int argc, int file[2], char *argv[], int fd[argc - 4][2])
{
	int index;

	index = 0;
	while (index < argc - 4)
	{
		if (pipe(fd[index]) < 0)
			broken_pipe();
		index++;
	}
	if (argc < 5)
		usage_error();
	file[0] = open(argv[1], O_RDONLY);
	file[1] = open(argv[argc - 1], O_WRONLY);
	if (file[0] < 0 || file[1] < 0)
		open_error();
}

void	close_first_pipes(int used_pipe, int argc, int fd[argc - 4][2])
{
	int index;

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

void	close_last_pipes(int used_pipe, int argc, int fd[argc - 4][2])
{
	int index;

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

void	close_pipes(int used_pipe, int argc, int fd[argc - 4][2])
{
	int index;

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

char	*find_path(char *command, char **env)
{
	char	**path;
	char	*command_path;
	char	*temp;
	int		index;

	index = 0;
	while (env[index])
	{
		if (strncmp("PATH=", env[index++], 5) == 0)
			path = ft_split(&env[index - 1][5], ':');
	}
	index = 0;
	while (path[index])
	{
		if (access(command, F_OK | X_OK) == 0)
			return (command);
		temp = ft_strjoin(path[index], "/");
		free(path[index++]);
		command_path = ft_strjoin(temp, command);
		free(temp);
		if (access(command_path, F_OK | X_OK) == 0)
			return (command_path);
		free(command_path);
	}
	return ((char *)wrong_path);
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
	if (execve(path, arguments, env) == -1)
		wrong_path();
	return (0);
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
	trimmed = (char **)malloc((index + 1) * sizeof(char *));
	index = 0;
	while (args[index])
	{
		trimmed[index] = ft_strtrim2(args[index], "'\"");
		free(args[index]);
		index++;
	}
	trimmed[index] = NULL;
	free(args);
	return (trimmed);
}
