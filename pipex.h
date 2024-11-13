/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joltmann <joltmann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 21:31:39 by joltmann          #+#    #+#             */
/*   Updated: 2024/11/13 22:26:14 by joltmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft/libft.h"
# include <fcntl.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_split_vars
{
	int		i;
	int		j;
	bool	in_single_quote;
	bool	in_double_quote;
	char	**args;
	char	*token;
}			t_split_vars;

typedef struct s_pipex_data
{
    int     argc;
    char    **argv;
    char    **envp;
    int     fd_in;
    int     fd_out;
    pid_t   *pids;
    int     pid_index;
    pid_t   last_pid;
}   		t_pipex_data;

//error_exit.c
void		error_exit(const char *msg);
void		infile_error_exit(const char *filename);

// exec_commands_helpers.c
char		**get_command_args(char *cmd);
char		*get_env_var(char *name, char **envp);
char		*get_path_env(char **envp);
char		*build_full_path(char *dir, char *cmd);
void		execute_full_path(char *full_path, char **args, char **envp);

// exec_commands.c
int			search_and_execute(char **args, char *path_env, char **envp);
void		execute_command_directly(char **args, char **envp);
void		command_not_found(char **args);
void		execute_command(char *cmd, char **envp);

// file_operations.c
void		open_files(t_pipex_data *data);

//pipex_utils.c
void		cleanup_paths(char **paths);
char		**parse_command(const char *cmd);

// pipex.c
void		pipex(int argc, char **argv, char **envp);
void		init_pipex_data(t_pipex_data *data, int argc, char **argv, char **envp);
int			wait_for_children(pid_t *pids, int num_pids, pid_t last_pid);

// process_management.c
void		process_commands(t_pipex_data *data);
void		process_last_command(t_pipex_data *data);
void		execute_child(t_pipex_data *data, int fd_in, int pipe_fd[2], int cmd_index);
void		update_parent(t_pipex_data *data, int *fd_in, int pipe_fd[2], pid_t pid);

// split_with_quotes.c
char		**split_with_quotes(const char *cmd);

#endif