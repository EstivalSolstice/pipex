/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_commands_helpers.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joltmann <joltmann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 21:47:44 by joltmann          #+#    #+#             */
/*   Updated: 2024/11/13 23:00:53 by joltmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**get_command_args(char *cmd)
{
	char	**args;

	args = parse_command(cmd);
	if (!args || !args[0])
		error_exit("Command parsing failed");
	return (args);
}

char	*get_env_var(char *name, char **envp)
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

char	*get_path_env(char **envp)
{
	char	*path_env;

	path_env = get_env_var("PATH", envp);
	if (!path_env)
		path_env = "/bin:/usr/bin";
	return (path_env);
}

char	*build_full_path(char *dir, char *cmd)
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

void	execute_full_path(char *full_path, char **args, char **envp)
{
	if (access(full_path, X_OK) == 0)
	{
		execve(full_path, args, envp);
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
