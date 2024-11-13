/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joltmann <joltmann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 21:31:44 by joltmann          #+#    #+#             */
/*   Updated: 2024/11/13 21:42:30 by joltmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void error_exit(const char *msg)
{
    ft_putstr_fd("pipex: ", 2);
    ft_putendl_fd((char *)msg, 2);
    exit(EXIT_FAILURE);
}

void infile_error_exit(const char *filename)
{
    ft_putstr_fd("pipex: ", 2);
    perror(filename);
    exit(0);
}

void	cleanup_paths(char **paths)
{
	int i;

	i = 0;
	while (paths[i])
	{
		free(paths[i]);
		i++;
	}
	free(paths);
}

char *get_env_var(char *name, char **envp)
{
    size_t  len;
    int     i;

	len = ft_strlen(name);
	i = 0;
	if (!envp)
        return (NULL);
    while (envp[i])
    {
        if (ft_strncmp(envp[i], name, len) == 0 && envp[i][len] == '=')
            return (&envp[i][len + 1]);
        i++;
    }
    return (NULL);
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
		{
			last_status = status;
		}
		i++;
	}
	return (last_status);
}

// char	**split_with_quotes(const char *cmd)
// {
// 	int		i;
// 	int		j;
// 	bool	in_single_quote;
// 	bool	in_double_quote;
// 	char	**args;
// 	char	*token;

// 	i = 0;
// 	j = 0;
// 	in_single_quote = false;
// 	in_double_quote = false;
// 	args = malloc(256 * sizeof(char *));
// 	token = malloc(ft_strlen(cmd) + 1);
// 	i = 0, j = 0;
// 	in_single_quote = false, in_double_quote = false;
// 	if (!args || !token)
// 		error_exit("Malloc failed for command parsing");
// 	while (*cmd)
// 	{
// 		if (*cmd == '\'' && !in_double_quote)
// 			in_single_quote = !in_single_quote;
// 		else if (*cmd == '"' && !in_single_quote)
// 			in_double_quote = !in_double_quote;
// 		else if (*cmd == ' ' && !in_single_quote && !in_double_quote)
// 		{
// 			if (j > 0)
// 			{
// 				token[j] = '\0';
// 				args[i++] = ft_strdup(token);
// 				if (!args[i - 1])
// 				{
// 					for (int k = 0; k < i - 1; k++)
// 						free(args[k]);
// 					free(args);
// 					free(token);
// 					return (NULL);
// 				}
// 				j = 0;
// 			}
// 		}
// 		else
// 			token[j++] = *cmd;
// 		cmd++;
// 	}
// 	if (j > 0)
// 	{
// 		token[j] = '\0';
// 		args[i++] = ft_strdup(token);
// 		if (!args[i - 1])
// 		{
// 			for (int k = 0; k < i - 1; k++)
// 				free(args[k]);
// 			free(args);
// 			free(token);
// 			return (NULL);
// 		}
// 	}
// 	args[i] = NULL;
// 	free(token);
// 	return (args);
// }

char	**parse_command(const char *cmd)
{
	char	**args;

	args = split_with_quotes(cmd);
	if (!args)
		error_exit("Command parsing failed");
	return (args);
}

void	execute_command(char *cmd, char **envp)
{
	char	**args;
	char	*path_env;
	char	*paths;
	char	*path_token;
	char	*full_path;

	args = parse_command(cmd);
	if (!args || !args[0])
		error_exit("Command parsing failed");
	path_env = get_env_var("PATH", envp);
	if (!path_env)
		path_env = "/bin:/usr/bin";
	paths = ft_strdup(path_env);
	if (!paths)
		error_exit("Malloc failed");
	path_token = strtok(paths, ":");
	while (path_token)
	{
		full_path = malloc(strlen(path_token) + ft_strlen(args[0]) + 2);
		if (!full_path)
			error_exit("Malloc failed");
		sprintf(full_path, "%s/%s", path_token, args[0]);
		if (access(full_path, F_OK) == 0)
		{
			if (access(full_path, X_OK) == 0)
			{
				execve(full_path, args, envp);
				perror(args[0]);
				free(full_path);
				cleanup_paths(args);
				free(paths);
				exit(EXIT_FAILURE);
			}
			else
			{
				ft_putstr_fd(args[0], 2);
				ft_putendl_fd(": Permission denied", 2);
				free(full_path);
				cleanup_paths(args);
				free(paths);
				exit(126);
			}
		}
		free(full_path);
		path_token = strtok(NULL, ":");
	}
	free(paths);
	if (access(args[0], F_OK) == 0)
	{
		if (access(args[0], X_OK) == 0)
		{
			execve(args[0], args, envp);
			perror(args[0]);
			cleanup_paths(args);
			exit(EXIT_FAILURE);
		}
		else
		{
			ft_putstr_fd(args[0], 2);
			ft_putendl_fd(": Permission denied", 2);
			cleanup_paths(args);
			exit(126);
		}
	}
	else
	{
		ft_putstr_fd("pipex: ", 2);
		ft_putstr_fd(args[0], 2);
		ft_putendl_fd(": command not found", 2);
		cleanup_paths(args);
		exit(127);
	}
}

void	pipex(int argc, char **argv, char **envp)
{
	int		pipe_fd[2];
	pid_t	pid;
	pid_t	pids[argc - 3];
	pid_t	last_pid;
	int		pid_index;
	int		i;
	int		status;
	int		fd_in;
	int		fd_out;

	pid_index = 0;
	last_pid = 0;
	i = 2;
	fd_in = open(argv[1], O_RDONLY);
	if (fd_in == -1)
	{
   		ft_putstr_fd("pipex: ", 2);
		perror(argv[1]);
   		fd_in = open("/dev/null", O_RDONLY);
    	if (fd_in == -1)
        	error_exit("Failed to open /dev/null");
	}
	fd_out = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd_out == -1)
		error_exit("Error opening outfile");
	while (i < argc - 2)
	{
		if (pipe(pipe_fd) == -1)
			error_exit("Pipe creation failed");
		pid = fork();
		if (pid == -1)
			error_exit("Fork failed");
		if (pid == 0)
		{
			close(pipe_fd[0]);
			dup2(fd_in, STDIN_FILENO);
			dup2(pipe_fd[1], STDOUT_FILENO);
			close(pipe_fd[1]);
			execute_command(argv[i], envp);
		}
		else
		{
			close(pipe_fd[1]);
			close(fd_in);
			fd_in = pipe_fd[0];
			pids[pid_index++] = pid;
		}
		i++;
	}
	pid = fork();
	if (pid == -1)
		error_exit("Fork failed");
	if (pid == 0)
	{
		dup2(fd_in, STDIN_FILENO);
		dup2(fd_out, STDOUT_FILENO);
		close(fd_in);
		close(fd_out);
		execute_command(argv[i], envp);
	}
	else
	{
		close(fd_in);
		close(fd_out);
		last_pid = pid;
		pids[pid_index++] = pid;
	}
	status = wait_for_children(pids, pid_index, last_pid);
	if (WIFEXITED(status))
		exit(WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		exit(128 + WTERMSIG(status));
	else
		exit(EXIT_FAILURE);
}

int main(int argc, char **argv, char **envp)
{
    if (argc < 5)
    {
        ft_putstr_fd("Usage: ", 2);
        ft_putstr_fd(argv[0], 2);
        ft_putendl_fd(" infile cmd1 cmd2 ... cmdN outfile", 2);
        return (1);
    }
    pipex(argc, argv, envp);
    return (0);
}
