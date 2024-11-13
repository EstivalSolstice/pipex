/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joltmann <joltmann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 22:42:38 by joltmann          #+#    #+#             */
/*   Updated: 2024/11/13 23:11:23 by joltmann         ###   ########.fr       */
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

// char	**parse_command(const char *cmd)
// {
// 	char	**args;
// 	char	*arg;
// 	size_t	arg_len;
// 	size_t	args_count;
// 	int		i;
// 	int		state;

// 	args = NULL;
// 	arg = NULL;
// 	arg_len = 0;
// 	args_count = 0;
// 	i = 0;
// 	state = 0;
// 	while (cmd[i])
// 	{
// 		if ((cmd[i] == ' ' || cmd[i] == '\t') && state == 0)
// 		{
// 			if (arg_len > 0)
// 			{
// 				arg = ft_strndup(arg, arg_len);
// 				args = ft_realloc_array(args, args_count + 1);
// 				args[args_count++] = arg;
// 				arg = NULL;
// 				arg_len = 0;
// 			}
// 			i++;
// 			continue ;
// 		}
// 		else if (cmd[i] == '\'' && state != IN_DOUBLE_QUOTE)
// 		{
// 			state = (state == IN_SINGLE_QUOTE) ? 0 : IN_SINGLE_QUOTE;
// 			i++;
// 			continue ;
// 		}
// 		else if (cmd[i] == '"' && state != IN_SINGLE_QUOTE)
// 		{
// 			state = (state == IN_DOUBLE_QUOTE) ? 0 : IN_DOUBLE_QUOTE;
// 			i++;
// 			continue ;
// 		}
// 		arg = ft_realloc(arg, arg_len, arg_len + 2);
// 		arg[arg_len++] = cmd[i++];
// 		arg[arg_len] = '\0';
// 	}
// 	if (arg_len > 0)
// 	{
// 		arg = ft_strndup(arg, arg_len);
// 		args = ft_realloc_array(args, args_count + 1);
// 		args[args_count++] = arg;
// 	}
// 	args = ft_realloc_array(args, args_count + 1);
// 	args[args_count] = NULL;
// 	return (args);
// }
