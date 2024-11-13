/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_operations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joltmann <joltmann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 22:10:18 by joltmann          #+#    #+#             */
/*   Updated: 2024/11/13 22:10:27 by joltmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void open_files(t_pipex_data *data)
{
    data->fd_in = open(data->argv[1], O_RDONLY);
    if (data->fd_in == -1)
    {
        ft_putstr_fd("pipex: ", 2);
        perror(data->argv[1]);
        data->fd_in = open("/dev/null", O_RDONLY);
        if (data->fd_in == -1)
            error_exit("Failed to open /dev/null");
    }
    data->fd_out = open(data->argv[data->argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (data->fd_out == -1)
        error_exit("Error opening outfile");
}
