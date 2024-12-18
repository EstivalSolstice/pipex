/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joltmann <joltmann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 21:48:36 by joltmann          #+#    #+#             */
/*   Updated: 2024/12/18 20:14:46 by joltmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	execute_command_directly(char **args, char **envp)
{
	if (access(args[0], F_OK) == 0)
	{
		if (access(args[0], X_OK) == 0)
		{
			execve(args[0], args, envp);
			perror(args[0]);
			cleanup_paths(args);
			exit(EXIT_FAILURE);
		}
		else
		{
			ft_putstr_fd(args[0], 2);
			ft_putendl_fd(": Permission denied", 2);
			cleanup_paths(args);
			exit(126);
		}
	}
}

void	command_not_found(char **args)
{
	ft_putstr_fd("pipex: ", 2);
	ft_putstr_fd(args[0], 2);
	ft_putendl_fd(": command not found", 2);
	cleanup_paths(args);
	exit(127);
}

void	execute_command(char *cmd, char **envp)
{
	char	**args;
	char	*path_env;
	int		not_found;

	args = get_command_args(cmd);
	path_env = get_path_env(envp);
	not_found = search_and_execute(args, path_env, envp);
	if (not_found)
	{
		execute_command_directly(args, envp);
		command_not_found(args);
	}
}
