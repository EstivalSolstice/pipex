/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_operations_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joltmann <joltmann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 22:10:18 by joltmann          #+#    #+#             */
/*   Updated: 2024/11/30 21:27:11 by joltmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

// void	open_files_bonus(t_pipex_data *data)
// {
// 	data->fd_in = open(data->argv[1], O_RDONLY);
// 	if (data->fd_in < 0)
// 		error_exit_bonus("Failed to open input file");
// 	data->fd_out = open(data->argv[data->argc - 1],
// 			O_WRONLY | O_CREAT | O_TRUNC, 0644);
// 	if (data->fd_out < 0)
// 		error_exit_bonus("Failed to open output file");
// }

void open_files_bonus(t_pipex_data *data) {
    data->fd_in = open(data->argv[1], O_RDONLY);
    if (data->fd_in < 0)
	{
        perror("pipex: input");
        data->fd_in = -1;
    }
    data->fd_out = open(data->argv[data->argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (data->fd_out < 0)
	{
        perror("pipex: input");
        exit(1);
    }
}

void	open_files_here_doc_bonus(t_pipex_data *data)
{
	data->fd_in = -1;
	data->fd_out = open(data->argv[data->argc - 1],
			O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (data->fd_out < 0)
		error_exit_bonus("input");
}
