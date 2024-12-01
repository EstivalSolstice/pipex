/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joltmann <joltmann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 22:01:26 by joltmann          #+#    #+#             */
/*   Updated: 2024/12/01 15:14:31 by joltmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	cleanup_paths_bonus(char **paths)
{
	int	i;

	i = 0;
	while (paths[i])
	{
		free(paths[i]);
		i++;
	}
	free(paths);
}

void	free_array_bonus(char **array)
{
	int	i;

	i = 0;
	if (!array)
		return ;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

char	*ft_strndup(const char *s, size_t n)
{
	char	*dup;

	dup = malloc(n + 1);
	if (!dup)
		return (NULL);
	ft_strlcpy(dup, s, n + 1);
	dup[n] = '\0';
	return (dup);
}

char	**ft_realloc_array_bonus(char **array, size_t old_size, size_t new_size)
{
	char	**new_array;
	size_t	i;

	i = 0;
	new_array = malloc(new_size * sizeof(char *));
	if (!new_array)
	{
		free_array_bonus(array);
		return (NULL);
	}
	while (i < old_size && i < new_size)
	{
		new_array[i] = array[i];
		i++;
	}
	free(array);
	return (new_array);
}

void	*ft_realloc_bonus(void *ptr, size_t old_size, size_t new_size)
{
	void	*new_ptr;

	if (new_size == 0)
	{
		free(ptr);
		return (NULL);
	}
	if (!ptr)
		return (malloc(new_size));
	new_ptr = malloc(new_size);
	if (!new_ptr)
		return (NULL);
	if (old_size > new_size)
		ft_memcpy(new_ptr, ptr, new_size);
	else
		ft_memcpy(new_ptr, ptr, old_size);
	free(ptr);
	return (new_ptr);
}
