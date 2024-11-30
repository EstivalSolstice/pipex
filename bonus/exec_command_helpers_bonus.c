/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command_helpers_bonus.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joltmann <joltmann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 21:47:44 by joltmann          #+#    #+#             */
/*   Updated: 2024/11/30 21:26:11 by joltmann         ###   ########.fr       */
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

char	*get_env_var_bonus(char *name, char **envp)
{
	size_t	len;
	int		i;

	len = ft_strlen(name);
	i = 0;
	if (!envp)
		return (NULL);
	while (envp[i])
	{
		if (ft_strncmp(envp[i], name, len) == 0 && envp[i][len] == '=')
			return (&envp[i][len + 1]);
		i++;
	}
	return (NULL);
}

char	*get_path_env_bonus(char **envp)
{
	char	*path_env;

	path_env = get_env_var_bonus("PATH", envp);
	if (!path_env)
		path_env = "/bin:/usr/bin";
	return (path_env);
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
