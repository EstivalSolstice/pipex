/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_management.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joltmann <joltmann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 22:10:50 by joltmann          #+#    #+#             */
/*   Updated: 2025/01/25 22:19:40 by joltmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	process_commands(t_pipex_data *data)
{
	int	i;
	int	fd_in;

	fd_in = data->fd_in;
	i = 2;
	while (i < data->argc - 2)
	{
		process_single_command(data, &fd_in, i);
		i++;
	}
	data->fd_in = fd_in;
}

void	process_single_command(t_pipex_data *data, int *fd_in, int cmd_index)
{
	int		pipe_fd[2];
	pid_t	pid;

	if (*fd_in == -1)
	{
		*fd_in = open("/dev/null", O_RDONLY);
		if (*fd_in == -1)
			error_exit("pipex: Failed to open /dev/null");
	}
	if (pipe(pipe_fd) == -1)
		error_exit("Pipe creation failed");
	pid = fork();
	if (pid == -1)
		error_exit("Fork failed");
	if (pid == 0)
	{
		execute_child(data, *fd_in, pipe_fd, cmd_index);
	}
	else
	{
		update_parent(data, fd_in, pipe_fd, pid);
	}
}

void	process_last_command(t_pipex_data *data)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		error_exit("Fork failed");
	if (pid == 0)
	{
		execute_last_child(data);
	}
	else
	{
		close(data->fd_in);
		close(data->fd_out);
		data->last_pid = pid;
		data->pids[data->pid_index++] = pid;
	}
}
