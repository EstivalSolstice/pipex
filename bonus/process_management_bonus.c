/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_management_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joltmann <joltmann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 22:10:50 by joltmann          #+#    #+#             */
/*   Updated: 2024/11/30 22:36:07 by joltmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	process_commands_bonus(t_pipex_data *data)
{
	int	i;
	int	fd_in;
	int	start_index;
	int	end_index;
	int is_last_command;

	fd_in = data->fd_in;
	if (fd_in == -1)
    {
        fd_in = open("/dev/null", O_RDONLY);
        if (fd_in == -1)
            error_exit_bonus("Failed to open /dev/null");
    }
	if (data->is_here_doc)
		start_index = 3;
	else
		start_index = 2;
	end_index = data->argc - 2;
	i = start_index;
    while (i <= end_index)
    {
        process_single_command_bonus(data, &fd_in, i);
        i++;
    }
    data->fd_in = fd_in;
}

void	process_single_command_bonus(t_pipex_data *data, int *fd_in, int cmd_index)
{
	int		pipe_fd[2];
	pid_t	pid;

    if (pipe(pipe_fd) == -1)
        error_exit_bonus("Pipe creation failed");
    else
        pipe_fd[1] = data->fd_out;
	if (pipe(pipe_fd) == -1)
		error_exit_bonus("Pipe creation failed");
	pid = fork();
	if (pid == -1)
		error_exit_bonus("Fork failed");
	if (pid == 0)
	{
		execute_child_bonus(data, *fd_in, pipe_fd, cmd_index);
	}
	else
	{
		update_parent_bonus(data, fd_in, pipe_fd, pid);
	}
}

void	process_last_command_bonus(t_pipex_data *data)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		error_exit_bonus("Fork failed");
	if (pid == 0)
	{
		execute_last_child_bonus(data);
	}
	else
	{
		if (data->fd_in != -1)
            close(data->fd_in);
		close(data->fd_out);
		data->last_pid = pid;
		data->pids[data->pid_index++] = pid;
	}
}
