/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_management_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joltmann <joltmann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 22:10:50 by joltmann          #+#    #+#             */
/*   Updated: 2025/01/24 04:04:19 by joltmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	init_fd_in(t_pipex_data *data)
{
	int	fd_in;

	fd_in = data->fd_in;
	if (fd_in == -1)
	{
		fd_in = open("/dev/null", O_RDONLY);
		if (fd_in == -1)
			error_exit_bonus("Failed to open /dev/null");
	}
	return (fd_in);
}

void	set_cmd_indices(t_pipex_data *data, int *start, int *end)
{
	if (data->is_here_doc)
		*start = 3;
	else
		*start = 2;
	*end = data->argc - 2;
}

void	process_commands_bonus(t_pipex_data *data)
{
	int	i;
	int	fd_in;
	int	start_index;
	int	end_index;

	fd_in = init_fd_in(data);
	set_cmd_indices(data, &start_index, &end_index);
	i = start_index;
	while (i <= end_index)
	{
		data->is_last_command = (i == end_index);
		process_single_command_bonus(data, &fd_in, i);
		i++;
	}
	data->fd_in = fd_in;
}

void	setup_pipes(t_pipex_data *data, int pipe_fd[2])
{
	if (!data->is_last_command)
	{
		if (pipe(pipe_fd) == -1)
			error_exit_bonus("Pipe creation failed");
	}
	else
	{
		pipe_fd[0] = -1;
		pipe_fd[1] = data->fd_out;
	}
}

void	process_single_command_bonus(t_pipex_data *data, int *fd_in,
		int cmd_index)
{
	int		pipe_fd[2];
	pid_t	pid;

	setup_pipes(data, pipe_fd);
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
