/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_token_to_args_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joltmann <joltmann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 16:07:10 by joltmann          #+#    #+#             */
/*   Updated: 2024/12/01 16:07:30 by joltmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	handle_error_bonus(t_split_vars *v)
{
	free_args_up_to_index_bonus(v->args, v->i);
	free(v->args);
	free(v->token);
	error_exit_bonus("Malloc failed for command parsing");
	return (0);
}

int	add_token_to_args_bonus(t_split_vars *v)
{
	size_t	old_size;
	size_t	new_size;
	char	**new_args;

	v->token[v->j] = '\0';
	if (v->i >= v->args_capacity)
	{
		old_size = v->args_capacity * sizeof(char *);
		v->args_capacity *= 2;
		new_size = v->args_capacity * sizeof(char *);
		new_args = ft_realloc_bonus(v->args, old_size, new_size);
		if (!new_args)
			return (handle_error_bonus(v));
		v->args = new_args;
	}
	v->args[v->i] = ft_strdup(v->token);
	if (!v->args[v->i])
		return (handle_error_bonus(v));
	v->i++;
	v->j = 0;
	return (1);
}
