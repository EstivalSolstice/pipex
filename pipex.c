/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joltmann <joltmann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 22:08:35 by joltmann          #+#    #+#             */
/*   Updated: 2025/01/25 22:01:29 by joltmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	pipex(int argc, char **argv, char **envp)
{
	t_pipex_data	data;
	int				status;
	int				init_status;

	init_status = 0;
	init_pipex_data(&data, argc, argv, envp);
	open_files(&data);
	process_commands(&data);
	process_last_command(&data);
	status = wait_for_children(data.pids, data.pid_index, init_status);
	free(data.pids);
	exit(status);
}

void	init_pipex_data(t_pipex_data *data, int argc, char **argv, char **envp)
{
	data->argc = argc;
	data->argv = argv;
	data->envp = envp;
	data->fd_in = -1;
	data->fd_out = -1;
	data->pid_index = 0;
	data->last_pid = 0;
	data->pids = malloc(sizeof(pid_t) * (argc - 3));
	if (!data->pids)
		error_exit("Malloc failed");
}

int	wait_for_children(pid_t *pids, int num_pids, int status)
{
	int	exit_code;
	int	child_exit_code;
	int	i;

	i = 0;
	exit_code = 0;
	while (i < num_pids)
	{
		if (waitpid(pids[i], &status, 0) == -1)
		{
			perror("waitpid");
			continue ;
		}
		if (WIFEXITED(status))
		{
			child_exit_code = WEXITSTATUS(status);
			if (i == num_pids - 1)
				exit_code = child_exit_code;
		}
		else if (WIFSIGNALED(status))
			if (i == num_pids - 1)
				exit_code = 128 + WTERMSIG(status);
		i++;
	}
	return (exit_code);
}
