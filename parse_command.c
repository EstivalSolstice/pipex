/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joltmann <joltmann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 22:42:38 by joltmann          #+#    #+#             */
/*   Updated: 2024/12/18 20:15:09 by joltmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	initialize_parser(t_parser *parser, const char *cmd)
{
	parser->args = NULL;
	parser->arg = NULL;
	parser->arg_len = 0;
	parser->args_count = 0;
	parser->i = 0;
	parser->state = 0;
	parser->cmd = cmd;
}

char	**parse_command(const char *cmd)
{
	t_parser	parser;

	initialize_parser(&parser, cmd);
	while (cmd[parser.i])
	{
		if ((cmd[parser.i] == ' ' || cmd[parser.i] == '\t')
			&& parser.state == 0)
		{
			handle_whitespace(&parser);
			continue ;
		}
		if (cmd[parser.i] == '\'' && parser.state != IN_DOUBLE_QUOTE)
		{
			handle_single_quote(&parser);
			continue ;
		}
		if (cmd[parser.i] == '"' && parser.state != IN_SINGLE_QUOTE)
		{
			handle_double_quote(&parser);
			continue ;
		}
		append_char_to_arg(&parser);
	}
	finalize_arg(&parser);
	return (parser.args);
}
