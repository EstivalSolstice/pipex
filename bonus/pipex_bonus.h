/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joltmann <joltmann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 20:45:44 by joltmann          #+#    #+#             */
/*   Updated: 2024/12/01 00:20:16 by joltmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

#include "pipex.h"

void	try_execve_bonus(char *full_path, char **args, char **envp);
int		search_in_paths_bonus(char **paths, char **args, char **envp);
int		search_and_execute_bonus(char **args, char *path_env, char **envp);
void	execute_command_directly_bonus(char **args, char **envp);
void	execute_command_bonus(t_pipex_data *data, char *cmd, char **envp);
void	process_single_command_bonus(t_pipex_data *data, int *fd_in,
				int cmd_idx);
void	process_last_command_bonus(t_pipex_data *data);
void	process_commands_bonus(t_pipex_data *data);
void	init_pipex_data_bonus(t_pipex_data *data, int argc, char **argv, char **envp);
void	pipex_bonus(int argc, char **argv, char **envp);
void	cleanup_paths_bonus(char **paths);
void	free_array_bonus(char **array);
char	*ft_strndup(const char *s, size_t n);
char	**ft_realloc_array_bonus(char **array, size_t new_size);
void	handle_whitespace_bonus(t_parser *parser);
void	handle_single_quote_bonus(t_parser *parser);
void	handle_double_quote_bonus(t_parser *parser);
void	append_char_to_arg_bonus(t_parser *parser);
void	finalize_arg_bonus(t_parser *parser);
char	**split_with_quotes_bonus(const char *cmd);
char	**get_command_args_bonus(char *cmd);
char	*get_env_var_bonus(char *name, char **envp);
char	*get_path_env_bonus(char **envp);
char	*build_full_path_bonus(char *dir, char *cmd);
void	execute_last_child_bonus(t_pipex_data *data);
void	execute_child_bonus(t_pipex_data *data, int fd_in, int pipe_fd[2],
			int cmd_index);
void	error_exit_bonus(const char *msg);
void	open_files_here_doc_bonus(t_pipex_data *data);
void	open_files_bonus(t_pipex_data *data);
void	handle_here_doc_bonus(t_pipex_data *data, char *limiter);
void	read_here_doc_input_bonus(int write_fd, char *limiter);
int		wait_for_children_bonus(pid_t *pids, int num_pids);
void	infile_error_exit_bonus(const char *filename);
void	update_parent_bonus(t_pipex_data *data, int *fd_in, int pipe_fd[2],
			pid_t pid);
void	*ft_realloc_bonus(void *ptr, size_t old_size, size_t new_size);
char	**ft_split_bonus(const char *s, char c);
char	*ft_strjoin_bonus(char const *s1, char const *s2);
char	**ft_realloc_array_bonus(char **array, size_t new_size);
void	command_not_found_bonus(char **args);
void	execute_full_path_bonus(char *full_path, char **args, char **envp);
char	**parse_command_bonus(const char *cmd);
char	*resolve_command(char *cmd, char **envp);
void	free_split(char **split_array);

#endif