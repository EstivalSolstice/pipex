/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_management.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joltmann <joltmann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 22:10:50 by joltmann          #+#    #+#             */
/*   Updated: 2024/11/13 22:10:59 by joltmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void process_commands(t_pipex_data *data)
{
    int     i;
    int     pipe_fd[2];
    pid_t   pid;
    int     fd_in;

    fd_in = data->fd_in;
    i = 2;
    while (i < data->argc - 2)
    {
        if (pipe(pipe_fd) == -1)
            error_exit("Pipe creation failed");
        pid = fork();
        if (pid == -1)
            error_exit("Fork failed");
        if (pid == 0)
            execute_child(data, fd_in, pipe_fd, i);
        else
            update_parent(data, &fd_in, pipe_fd, pid);
        i++;
    }
    data->fd_in = fd_in;
}

void process_last_command(t_pipex_data *data)
{
    pid_t   pid;

    pid = fork();
    if (pid == -1)
        error_exit("Fork failed");
    if (pid == 0)
    {
        dup2(data->fd_in, STDIN_FILENO);
        dup2(data->fd_out, STDOUT_FILENO);
        close(data->fd_in);
        close(data->fd_out);
        execute_command(data->argv[data->argc - 2], data->envp);
    }
    else
    {
        close(data->fd_in);
        close(data->fd_out);
        data->last_pid = pid;
        data->pids[data->pid_index++] = pid;
    }
}

void execute_child(t_pipex_data *data, int fd_in, int pipe_fd[2], int cmd_index)
{
    close(pipe_fd[0]);
    dup2(fd_in, STDIN_FILENO);
    dup2(pipe_fd[1], STDOUT_FILENO);
    close(pipe_fd[1]);
    execute_command(data->argv[cmd_index], data->envp);
}

void update_parent(t_pipex_data *data, int *fd_in, int pipe_fd[2], pid_t pid)
{
    close(pipe_fd[1]);
    close(*fd_in);
    *fd_in = pipe_fd[0];
    data->pids[data->pid_index++] = pid;
}
