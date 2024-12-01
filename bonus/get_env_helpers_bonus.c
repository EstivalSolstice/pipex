/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_helpers_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joltmann <joltmann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 16:05:32 by joltmann          #+#    #+#             */
/*   Updated: 2024/12/01 16:05:41 by joltmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

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
