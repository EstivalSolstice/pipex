/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joltmann <joltmann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 21:48:36 by joltmann          #+#    #+#             */
/*   Updated: 2025/01/25 20:01:01 by joltmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	free_args_bonus(char **args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		free(args[i]);
		i++;
	}
	free(args);
}

char	**get_cmd_args_bonus(char *cmd, t_pipex_data *data)
{
	char	**cmd_args;

	cmd_args = parse_command_bonus(cmd);
	if (!cmd_args || !cmd_args[0])
	{
		if (data->is_last_command)
		{
			ft_putstr_fd("pipex: ", STDERR_FILENO);
			ft_putstr_fd(cmd, STDERR_FILENO);
			ft_putendl_fd(": Invalid command", STDERR_FILENO);
		}
		if (cmd_args)
			free_args_bonus(cmd_args);
		exit(127);
	}
	return (cmd_args);
}

void	exec_command_bonus(char *cmd_path, char **cmd_args, char **envp)
{
	if (execve(cmd_path, cmd_args, envp) == -1)
	{
		perror("pipex: Execve failed");
		free(cmd_path);
		free_args_bonus(cmd_args);
		exit(1);
	}
}

char	*get_cmd_path_bonus(char *cmd_name, char **envp)
{
	char	*cmd_path;

	cmd_path = resolve_command_bonus(cmd_name, envp);
	if (!cmd_path)
	{
		ft_putstr_fd("pipex: ", STDERR_FILENO);
		ft_putstr_fd(cmd_name, STDERR_FILENO);
		ft_putendl_fd(": command not found", STDERR_FILENO);
		exit(127);
	}
	return (cmd_path);
}

void	execute_command_bonus(t_pipex_data *data, char *cmd, char **envp)
{
	char	*cmd_path;
	char	**cmd_args;

	cmd_args = get_cmd_args_bonus(cmd, data);
	cmd_path = get_cmd_path_bonus(cmd_args[0], envp);
	exec_command_bonus(cmd_path, cmd_args, envp);
}
