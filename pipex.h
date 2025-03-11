/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joltmann <joltmann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 21:31:39 by joltmann          #+#    #+#             */
/*   Updated: 2025/01/25 22:01:53 by joltmann         ###   ########.fr       */
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

# define IN_SINGLE_QUOTE 1
# define IN_DOUBLE_QUOTE 2

typedef struct s_split_vars
{
	int			i;
	int			j;
	bool		in_single_quote;
	bool		in_double_quote;
	char		**args;
	char		*token;
	int			args_capacity;
}				t_split_vars;

typedef struct s_pipex_data
{
	int			argc;
	char		**argv;
	char		**envp;
	int			fd_in;
	int			fd_out;
	pid_t		*pids;
	int			pid_index;
	pid_t		last_pid;
	int			is_here_doc;
	int			is_last_command;
}				t_pipex_data;

typedef struct s_parser
{
	char		**args;
	char		*arg;
	size_t		arg_len;
	size_t		args_count;
	int			i;
	int			state;
	const char	*cmd;
}				t_parser;

// error_exit.c
void			error_exit(const char *msg);
void			infile_error_exit(const char *filename);

// exec_commands_helpers.c
char			**get_command_args(char *cmd);
char			*get_env_var(char *name, char **envp);
char			*get_path_env(char **envp);
char			*build_full_path(char *dir, char *cmd);
void			execute_full_path(char *full_path, char **args, char **envp);

// exec_commands.c
void			execute_command_directly(char **args, char **envp);
void			command_not_found(char **args);
void			execute_command(char *cmd, char **envp);

// file_operations.c
void			open_files(t_pipex_data *data);
void			open_files_here_doc(t_pipex_data *data);

// pipex_utils.c
void			cleanup_paths(char **paths);
void			free_array(char **array);
char			*ft_strndup(const char *s, size_t n);
char			**ft_realloc_array(char **array, size_t new_size);
void			*ft_realloc(void *ptr, size_t old_size, size_t new_size);

// parse_command_helpers.c
void			handle_whitespace(t_parser *parser);
void			handle_single_quote(t_parser *parser);
void			handle_double_quote(t_parser *parser);
void			append_char_to_arg(t_parser *parser);
void			finalize_arg(t_parser *parser);

// parse_command.c
void			initialize_parser(t_parser *parser, const char *cmd);
char			**parse_command(const char *cmd);

// pipex.c
void			pipex(int argc, char **argv, char **envp);
void			init_pipex_data(t_pipex_data *data, int argc, char **argv,
					char **envp);
int				wait_for_children(pid_t *pids, int num_pids, int status);
void			handle_here_doc(t_pipex_data *data, char *limiter);
void			read_here_doc_input(int write_fd, char *limiter);

// process_handle_family.c
void			execute_last_child(t_pipex_data *data);
void			execute_child(t_pipex_data *data, int fd_in, int pipe_fd[2],
					int cmd_index);
void			update_parent(t_pipex_data *data, int *fd_in, int pipe_fd[2],
					pid_t pid);

// process_management.c
void			process_commands(t_pipex_data *data);
void			process_single_command(t_pipex_data *data, int *fd_in,
					int cmd_index);
void			process_last_command(t_pipex_data *data);

// search_and_exec.c
void			try_execve(char *full_path, char **args, char **envp);
int				search_in_paths(char **paths, char **args, char **envp);
int				search_and_execute(char **args, char *path_env, char **envp);

// split_with_quotes.c
char			**split_with_quotes(const char *cmd);

// debugging
void			try_execve_debug(char *full_path, char **args, char **envp);

#endif