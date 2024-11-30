/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command_helpers_bonus.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joltmann <joltmann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 23:10:08 by joltmann          #+#    #+#             */
/*   Updated: 2024/11/30 16:45:12 by joltmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	handle_whitespace_bonus(t_parser *parser)
{
	if (parser->arg_len > 0)
	{
		parser->arg = ft_strndup(parser->arg, parser->arg_len);
		parser->args = ft_realloc_array_bonus(parser->args, parser->args_count + 1);
		parser->args[parser->args_count++] = parser->arg;
		parser->arg = NULL;
		parser->arg_len = 0;
	}
	parser->i++;
}

void	handle_single_quote_bonus(t_parser *parser)
{
	if (parser->state == IN_SINGLE_QUOTE)
		parser->state = 0;
	else
		parser->state = IN_SINGLE_QUOTE;
	parser->i++;
}

void	handle_double_quote_bonus(t_parser *parser)
{
	if (parser->state == IN_DOUBLE_QUOTE)
		parser->state = 0;
	else
		parser->state = IN_DOUBLE_QUOTE;
	parser->i++;
}

	void	append_char_to_arg_bonus(t_parser *parser)
{
    void *new_arg = ft_realloc_bonus(parser->arg, parser->arg_len, parser->arg_len + 2);
    if (!new_arg)
        return ;
	parser->arg[parser->arg_len++] = parser->cmd[parser->i++];
	parser->arg[parser->arg_len] = '\0';
}

void	finalize_arg_bonus(t_parser *parser)
{
	if (parser->arg_len > 0)
	{
		parser->arg = ft_strndup(parser->arg, parser->arg_len);
		parser->args = ft_realloc_array_bonus(parser->args, parser->args_count + 1);
		parser->args[parser->args_count++] = parser->arg;
	}
	parser->args = ft_realloc_array_bonus(parser->args, parser->args_count + 1);
	parser->args[parser->args_count] = NULL;
}
