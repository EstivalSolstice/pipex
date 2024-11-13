/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command_helpers.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joltmann <joltmann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 23:10:08 by joltmann          #+#    #+#             */
/*   Updated: 2024/11/13 23:11:02 by joltmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	handle_whitespace(t_parser *parser)
{
	if (parser->arg_len > 0)
	{
		parser->arg = ft_strndup(parser->arg, parser->arg_len);
		parser->args = ft_realloc_array(parser->args, parser->args_count + 1);
		parser->args[parser->args_count++] = parser->arg;
		parser->arg = NULL;
		parser->arg_len = 0;
	}
	parser->i++;
}

void	handle_single_quote(t_parser *parser)
{
	if (parser->state == IN_SINGLE_QUOTE)
		parser->state = 0;
	else
		parser->state = IN_SINGLE_QUOTE;
	parser->i++;
}

void	handle_double_quote(t_parser *parser)
{
	if (parser->state == IN_DOUBLE_QUOTE)
		parser->state = 0;
	else
		parser->state = IN_DOUBLE_QUOTE;
	parser->i++;
}

void	append_char_to_arg(t_parser *parser)
{
	parser->arg = ft_realloc(parser->arg, parser->arg_len, parser->arg_len + 2);
	parser->arg[parser->arg_len++] = parser->cmd[parser->i++];
	parser->arg[parser->arg_len] = '\0';
}

void	finalize_arg(t_parser *parser)
{
	if (parser->arg_len > 0)
	{
		parser->arg = ft_strndup(parser->arg, parser->arg_len);
		parser->args = ft_realloc_array(parser->args, parser->args_count + 1);
		parser->args[parser->args_count++] = parser->arg;
	}
	parser->args = ft_realloc_array(parser->args, parser->args_count + 1);
	parser->args[parser->args_count] = NULL;
}
