/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwallier <rwallier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 17:01:03 by rwallier          #+#    #+#             */
/*   Updated: 2022/07/22 21:16:36 by rwallier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	initial_errors(int argc, int file[2], char *argv[], int **fd)
{
	int	index;

	index = 0;
	while (index < argc - 3)
	{
		if (pipe(fd[index++]) == -1)
			broken_pipe();
	}
	if (argc < 5)
		usage_error();
	if (ft_strncmp(argv[1], "here_doc", 8) == 0)
		open_heredoc(argv, file);
	else
		file[0] = open(argv[1], O_RDONLY);
	file[1] = open(argv[argc - 1], O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (file[0] < 0 || file[1] < 0)
		open_error();
}

void	open_heredoc(char *argv[], int file[2])
{
	int		here_doc;
	int		infile;
	char	*line;

	infile = open("tempfile", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	here_doc = open("here_doc", O_RDONLY);
	if (infile == -1 || here_doc == -1)
		open_error();
	line = get_next_line(here_doc);
	while (ft_strncmp(line, argv[2], ft_strlen(argv[2])))
	{
		ft_putstr_fd(line, infile);
		free(line);
		line = NULL;
		line = get_next_line(here_doc);
	}
	if (line)
		free(line);
	close(infile);
	file[0] = open("tempfile", O_RDONLY);
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
		if (ft_strncmp("PATH=", env[index++], 5) == 0)
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
