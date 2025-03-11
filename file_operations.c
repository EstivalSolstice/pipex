/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_operations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joltmann <joltmann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 22:10:18 by joltmann          #+#    #+#             */
/*   Updated: 2025/01/25 22:14:05 by joltmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	open_files(t_pipex_data *data)
{
	data->fd_out = open(data->argv[data->argc - 1],
			O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (data->fd_out == -1)
	{
		ft_putstr_fd("pipex: ", 2);
		perror(data->argv[data->argc - 1]);
		exit(EXIT_FAILURE);
	}
	data->fd_in = open(data->argv[1], O_RDONLY);
	if (data->fd_in == -1)
	{
		ft_putstr_fd("pipex: ", 2);
		perror(data->argv[1]);
		data->fd_in = -1;
	}
}
