/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joltmann <joltmann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 16:08:30 by joltmann          #+#    #+#             */
/*   Updated: 2024/12/01 16:08:36 by joltmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static void	read_and_write_here_doc(int write_fd, char *limiter)
{
	char	*line;

	while (1)
	{
		ft_putstr_fd("heredoc> ", STDOUT_FILENO);
		line = get_next_line(STDIN_FILENO);
		if (!line || (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0
				&& line[ft_strlen(limiter)] == '\n'))
		{
			free(line);
			break ;
		}
		ft_putstr_fd(line, write_fd);
		free(line);
	}
}

void	child_here_doc(int pipe_fd[2], char *limiter)
{
	close(pipe_fd[0]);
	read_and_write_here_doc(pipe_fd[1], limiter);
	close(pipe_fd[1]);
	exit(EXIT_SUCCESS);
}

void	parent_here_doc(t_pipex_data *data, int pipe_fd[2])
{
	close(pipe_fd[1]);
	data->fd_in = pipe_fd[0];
	wait(NULL);
}

void	handle_here_doc_bonus(t_pipex_data *data, char *limiter)
{
	int		here_doc_pipe[2];

	if (pipe(here_doc_pipe) == -1)
		error_exit_bonus("Pipe creation failed");
	if (fork() == 0)
		child_here_doc(here_doc_pipe, limiter);
	else
		parent_here_doc(data, here_doc_pipe);
}
