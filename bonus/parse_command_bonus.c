/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joltmann <joltmann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 22:42:38 by joltmann          #+#    #+#             */
/*   Updated: 2024/12/01 15:43:52 by joltmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

char	**parse_command_bonus(const char *cmd)
{
	return (split_with_quotes_bonus(cmd));
}

char	*resolve_command_bonus(char *cmd, char **envp)
{
	char	*path_env;
	char	**paths;
	char	*cmd_path;
	int		i;

	if (access(cmd, X_OK) == 0)
		return (ft_strdup(cmd));
	path_env = get_env_var_bonus("PATH", envp);
	if (!path_env)
		return (NULL);
	paths = ft_split(path_env, ':');
	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		cmd_path = ft_strjoin(ft_strjoin(paths[i], "/"), cmd);
		if (access(cmd_path, X_OK) == 0)
			return (free_split(paths), cmd_path);
		free(cmd_path);
		i++;
	}
	return (free_split(paths), NULL);
}

void	free_split(char **split_array)
{
	int	i;

	i = 0;
	if (!split_array)
		return ;
	while (split_array[i])
	{
		free(split_array[i]);
		i++;
	}
	free(split_array);
}
