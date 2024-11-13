/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_family.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joltmann <joltmann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 23:22:13 by joltmann          #+#    #+#             */
/*   Updated: 2024/11/13 23:24:47 by joltmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	execute_last_child(t_pipex_data *data)
{
	if (dup2(data->fd_in, STDIN_FILENO) == -1)
		error_exit("dup2 failed");
	if (dup2(data->fd_out, STDOUT_FILENO) == -1)
		error_exit("dup2 failed");
	close(data->fd_in);
	close(data->fd_out);
	execute_command(data->argv[data->argc - 2], data->envp);
}

void	execute_child(t_pipex_data *data, int fd_in, int pipe_fd[2],
		int cmd_index)
{
	if (dup2(fd_in, STDIN_FILENO) == -1)
		error_exit("dup2 failed");
	if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
		error_exit("dup2 failed");
	close(fd_in);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	execute_command(data->argv[cmd_index], data->envp);
}

void	update_parent(t_pipex_data *data, int *fd_in, int pipe_fd[2], pid_t pid)
{
	close(pipe_fd[1]);
	if (*fd_in != data->fd_in)
		close(*fd_in);
	*fd_in = pipe_fd[0];
	data->pids[data->pid_index++] = pid;
}
