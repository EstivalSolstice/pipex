/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joltmann <joltmann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 22:08:35 by joltmann          #+#    #+#             */
/*   Updated: 2024/12/01 16:08:18 by joltmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	pipex_bonus(int argc, char **argv, char **envp)
{
	t_pipex_data	data;
	int				exit_code;

	init_pipex_data_bonus(&data, argc, argv, envp);
	if (data.is_here_doc)
	{
		open_files_here_doc_bonus(&data);
		handle_here_doc_bonus(&data, argv[2]);
	}
	else
		open_files_bonus(&data);
	process_commands_bonus(&data);
	exit_code = wait_for_children_bonus(data.pids, data.pid_index);
	free(data.pids);
	exit(exit_code);
}

void	init_pipex_data_bonus(t_pipex_data *data, int argc, char **argv,
		char **envp)
{
	int	num_commands;

	data->argc = argc;
	data->argv = argv;
	data->envp = envp;
	data->fd_in = -1;
	data->fd_out = -1;
	data->pid_index = 0;
	data->is_here_doc = 0;
	if (ft_strncmp(argv[1], "here_doc", 8) == 0)
		data->is_here_doc = 1;
	else
		data->is_here_doc = 0;
	if (data->is_here_doc)
		num_commands = argc - 4;
	else
		num_commands = argc - 3;
	data->pids = malloc(sizeof(pid_t) * (num_commands + 1));
	if (!data->pids)
		error_exit_bonus("Malloc failed");
}

int	wait_for_children_bonus(pid_t *pids, int num_pids)
{
	int	status;
	int	exit_code;
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
		if (i == num_pids - 1)
		{
			if (WIFEXITED(status))
				exit_code = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				exit_code = 128 + WTERMSIG(status);
		}
		i++;
	}
	return (exit_code);
}

// void	handle_here_doc_bonus(t_pipex_data *data, char *limiter)
// {
// 	int		here_doc_pipe[2];
// 	char	*line;

// 	if (pipe(here_doc_pipe) == -1)
// 		error_exit_bonus("Pipe creation failed");
// 	if (fork() == 0)
// 	{
// 		close(here_doc_pipe[0]);
// 		while (1)
// 		{
// 			ft_putstr_fd("heredoc> ", STDOUT_FILENO);
// 			line = get_next_line(STDIN_FILENO);
// 			if (!line || (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0
// 					&& line[ft_strlen(limiter)] == '\n'))
// 			{
// 				free(line);
// 				break ;
// 			}
// 			ft_putstr_fd(line, here_doc_pipe[1]);
// 			free(line);
// 		}
// 		close(here_doc_pipe[1]);
// 		exit(EXIT_SUCCESS);
// 	}
// 	else
// 	{
// 		close(here_doc_pipe[1]);
// 		data->fd_in = here_doc_pipe[0];
// 		wait(NULL);
// 	}
// }

void	read_here_doc_input_bonus(int write_fd, char *limiter)
{
	char	*line;
	size_t	limiter_len;

	limiter_len = ft_strlen(limiter);
	while (1)
	{
		ft_putstr_fd("heredoc> ", STDOUT_FILENO);
		line = get_next_line(STDIN_FILENO);
		if (!line)
			break ;
		if (ft_strncmp(line, limiter, limiter_len) == 0
			&& line[limiter_len] == '\n')
		{
			free(line);
			break ;
		}
		ft_putstr_fd(line, write_fd);
		free(line);
	}
	close(write_fd);
}
