/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_and_exec_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joltmann <joltmann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 23:28:04 by joltmann          #+#    #+#             */
/*   Updated: 2024/11/30 20:59:55 by joltmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	try_execve_bonus(char *full_path, char **args, char **envp)
{
	if (access(full_path, F_OK | X_OK) == 0)
	{
		execve(full_path, args, envp);
		perror(args[0]);
		cleanup_paths_bonus(args);
		free(full_path);
		exit(EXIT_FAILURE);
	}
}

int	search_in_paths_bonus(char **paths, char **args, char **envp)
{
	char	*full_path;
	int		i;

	i = 0;
	while (paths[i])
	{
		full_path = build_full_path_bonus(paths[i], args[0]);
		if (!full_path)
			error_exit_bonus("Malloc failed");
		try_execve_bonus(full_path, args, envp);
		free(full_path);
		i++;
	}
	return (1);
}

int	search_and_execute_bonus(char **args, char *path_env, char **envp)
{
	char	**paths;
	int		not_found;

	paths = ft_split(path_env, ':');
	if (!paths)
		error_exit_bonus("Malloc failed");
	not_found = search_in_paths_bonus(paths, args, envp);
	free_array_bonus(paths);
	return (not_found);
}
