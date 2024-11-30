/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_family_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joltmann <joltmann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 23:22:13 by joltmann          #+#    #+#             */
/*   Updated: 2024/11/30 23:21:25 by joltmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

// void	execute_last_child_bonus(t_pipex_data *data)
// {
// 	int	last_cmd_index;

// 	if (data->is_here_doc)
// 		last_cmd_index = data->argc - 2;
// 	else
// 		last_cmd_index = data->argc - 2;
// 	if (data->fd_in == -1)
//     {
//         data->fd_in = open("/dev/null", O_RDONLY);
//         if (data->fd_in == -1)
//             error_exit_bonus("pipex: input /dev/null");
//     }
// 	if (dup2(data->fd_in, STDIN_FILENO) == -1)
// 		error_exit_bonus("dup2 failed");
// 	if (dup2(data->fd_out, STDOUT_FILENO) == -1)
// 		error_exit_bonus("dup2 failed");
// 	close(data->fd_in);
// 	close(data->fd_out);
// 	execute_command_bonus(data->argv[last_cmd_index], data->envp);
// }

void	close_fds_child(int fd_in, int pipe_fd[2],
			t_pipex_data *data)
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
	execute_command_bonus(data->argv[cmd_index], data->envp);
}


// void	execute_child_bonus(t_pipex_data *data, int fd_in, int pipe_fd[2],
// 			int cmd_index)
// {
// 	if (fd_in == -1)
//     {
//         fd_in = open("/dev/null", O_RDONLY);
//         if (fd_in == -1)
//             error_exit_bonus("pipex: input /dev/null");
//     }
// 	if (dup2(fd_in, STDIN_FILENO) == -1)
// 		error_exit_bonus("dup2 failed");
// 	if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
// 		error_exit_bonus("dup2 failed");
// 	close(fd_in);
// 	close(pipe_fd[0]);
// 	close(pipe_fd[1]);
// 	execute_command_bonus(data->argv[cmd_index], data->envp);
// }

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

// void	update_parent_bonus(t_pipex_data *data, int *fd_in, int pipe_fd[2], pid_t pid)
// {
// 	close(pipe_fd[1]);
// 	if (*fd_in != data->fd_in && *fd_in != -1)
// 		close(*fd_in);
// 	*fd_in = pipe_fd[0];
// 	data->pids[data->pid_index++] = pid;
// }
