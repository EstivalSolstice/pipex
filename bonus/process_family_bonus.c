/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_family_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joltmann <joltmann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 23:22:13 by joltmann          #+#    #+#             */
/*   Updated: 2025/01/24 04:03:41 by joltmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	close_fds_child(int fd_in, int pipe_fd[2], t_pipex_data *data)
{
	if (fd_in != data->fd_in)
		close(fd_in);
	if (!data->is_last_command)
	{
		close(pipe_fd[0]);
		close(pipe_fd[1]);
	}
	else
	{
		close(data->fd_out);
	}
}

void	execute_child_bonus(t_pipex_data *data, int fd_in, int pipe_fd[2],
		int cmd_index)
{
	if (fd_in == -1)
	{
		fd_in = open("/dev/null", O_RDONLY);
		if (fd_in == -1)
			error_exit_bonus("Failed to open /dev/null");
	}
	if (dup2(fd_in, STDIN_FILENO) == -1)
		error_exit_bonus("dup2 failed for stdin");
	if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
		error_exit_bonus("dup2 failed for stdout");
	close_fds_child(fd_in, pipe_fd, data);
	execute_command_bonus(data, data->argv[cmd_index], data->envp);
}

void	update_parent_bonus(t_pipex_data *data, int *fd_in, int pipe_fd[2],
		pid_t pid)
{
	if (!data->is_last_command)
	{
		close(pipe_fd[1]);
		if (*fd_in != data->fd_in && *fd_in != -1)
			close(*fd_in);
		*fd_in = pipe_fd[0];
	}
	else
	{
		if (*fd_in != data->fd_in && *fd_in != -1)
			close(*fd_in);
		close(data->fd_out);
	}
	data->pids[data->pid_index++] = pid;
}
