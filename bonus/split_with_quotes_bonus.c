/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_with_quotes_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joltmann <joltmann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 21:31:29 by joltmann          #+#    #+#             */
/*   Updated: 2024/11/30 16:54:20 by joltmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static int	init_split_vars_bonus(t_split_vars *v, const char *cmd)
{
	v->i = 0;
	v->j = 0;
	v->in_single_quote = false;
	v->in_double_quote = false;
	v->args_capacity = 10;
	v->args = malloc(v->args_capacity * sizeof(char *));
	v->token = malloc(ft_strlen(cmd) + 1);
	if (!v->args || !v->token)
	{
		error_exit_bonus("Malloc failed for command parsing");
		return (0);
	}
	return (1);
}

static int	add_token_to_args_bonus(t_split_vars *v)
{
	int		k;
	char	**new_args;

	v->token[v->j] = '\0';
	if (v->i >= v->args_capacity)
	{
		v->args_capacity *= 2;
		new_args = realloc(v->args, v->args_capacity * sizeof(char *));
		if (!new_args)
		{
			k = 0;
			while (k < v->i)
			{
				free(v->args[k]);
				k++;
			}
			free(v->args);
			free(v->token);
			error_exit_bonus("Malloc failed for command parsing");
			return (0);
		}
		v->args = new_args;
	}
	v->args[v->i] = ft_strdup(v->token);
	if (!v->args[v->i])
	{
		k = 0;
		while (k < v->i)
		{
			free(v->args[k]);
			k++;
		}
		free(v->args);
		free(v->token);
		error_exit_bonus("Malloc failed for command parsing");
		return (0);
	}
	v->i++;
	v->j = 0;
	return (1);
}

static int	process_cmd_bonus(t_split_vars *v, const char *cmd)
{
	while (*cmd)
	{
		if (*cmd == '\'' && !v->in_double_quote)
			v->in_single_quote = !v->in_single_quote;
		else if (*cmd == '"' && !v->in_single_quote)
			v->in_double_quote = !v->in_double_quote;
		else if (*cmd == ' ' && !v->in_single_quote && !v->in_double_quote)
		{
			if (v->j > 0)
			{
				if (!add_token_to_args_bonus(v))
					return (0);
			}
			v->j = 0;
		}
		else
		{
			v->token[v->j] = *cmd;
			v->j++;
		}
		cmd++;
	}
	return (1);
}

char	**split_with_quotes_bonus(const char *cmd)
{
	t_split_vars	v;

	if (!init_split_vars_bonus(&v, cmd))
		return (NULL);
	if (!process_cmd_bonus(&v, cmd))
		return (NULL);
	if (v.j > 0)
	{
		if (!add_token_to_args_bonus(&v))
			return (NULL);
	}
	v.args[v.i] = NULL;
	free(v.token);
	return (v.args);
}
