/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command_helpers_bonus.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joltmann <joltmann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 21:47:44 by joltmann          #+#    #+#             */
/*   Updated: 2025/01/24 04:46:21 by joltmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

char	**get_command_args_bonus(char *cmd)
{
	char	**args;

	args = parse_command_bonus(cmd);
	if (!args || !args[0])
		error_exit_bonus("Command parsing failed");
	return (args);
}

void	execute_command_directly_bonus(char **args, char **envp)
{
	if (access(args[0], F_OK) == 0)
	{
		if (access(args[0], X_OK) == 0)
		{
			execve(args[0], args, envp);
			perror(args[0]);
			cleanup_paths_bonus(args);
			exit(EXIT_FAILURE);
		}
		else
		{
			ft_putstr_fd(args[0], 2);
			ft_putendl_fd(": Permission denied", 2);
			cleanup_paths_bonus(args);
			exit(126);
		}
	}
	else
		command_not_found_bonus(args);
}

void	command_not_found_bonus(char **args)
{
	ft_putstr_fd("pipex: ", 2);
	ft_putstr_fd(args[0], 2);
	ft_putendl_fd(": command not found", 2);
	cleanup_paths_bonus(args);
	exit(127);
}

char	*build_full_path_bonus(char *dir, char *cmd)
{
	char	*temp;
	char	*full_path;

	if (!dir || !cmd)
		return (NULL);
	temp = ft_strjoin(dir, "/");
	if (!temp)
		return (NULL);
	full_path = ft_strjoin(temp, cmd);
	free(temp);
	return (full_path);
}

void	execute_full_path_bonus(char *full_path, char **args, char **envp)
{
	if (access(full_path, X_OK) == 0)
	{
		execve(full_path, args, envp);
		perror(args[0]);
		cleanup_paths_bonus(args);
		exit(EXIT_FAILURE);
	}
	else
	{
		ft_putstr_fd(args[0], 2);
		ft_putendl_fd(": Permission denied", 2);
		cleanup_paths_bonus(args);
		exit(126);
	}
}
