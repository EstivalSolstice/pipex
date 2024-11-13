/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joltmann <joltmann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 22:08:35 by joltmann          #+#    #+#             */
/*   Updated: 2024/11/13 23:04:21 by joltmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	pipex(int argc, char **argv, char **envp)
{
	t_pipex_data	data;
	int				status;

	init_pipex_data(&data, argc, argv, envp);
	open_files(&data);
	process_commands(&data);
	process_last_command(&data);
	status = wait_for_children(data.pids, data.pid_index, data.last_pid);
	free(data.pids);
	if (WIFEXITED(status))
		exit(WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		exit(128 + WTERMSIG(status));
	else
		exit(EXIT_FAILURE);
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

int	wait_for_children(pid_t *pids, int num_pids, pid_t last_pid)
{
	int		status;
	int		last_status;
	pid_t	wpid;
	int		i;

	last_status = 0;
	i = 0;
	while (i < num_pids)
	{
		wpid = waitpid(pids[i], &status, 0);
		if (wpid == -1)
			perror("waitpid");
		if (wpid == last_pid)
			last_status = status;
		i++;
	}
	return (last_status);
}
