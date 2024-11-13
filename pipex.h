/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joltmann <joltmann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 21:31:39 by joltmann          #+#    #+#             */
/*   Updated: 2024/11/13 21:32:20 by joltmann         ###   ########.fr       */
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

void		error_exit(const char *msg);
void		infile_error_exit(const char *filename);
void		cleanup_paths(char **paths);
char		*get_env_var(char *name, char **envp);
int			wait_for_children(pid_t *pids, int num_pids, pid_t last_pid);
char		**split_with_quotes(const char *cmd);

#endif