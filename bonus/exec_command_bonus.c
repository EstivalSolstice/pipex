/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joltmann <joltmann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 21:48:36 by joltmann          #+#    #+#             */
/*   Updated: 2024/11/30 23:04:23 by joltmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	execute_command_directly_bonus(char **args, char **envp)
{
	if (access(args[0], F_OK) == 0)
	{
		if (access(args[0], X_OK) == 0)
		{
			execve(args[0], args, envp);
			perror(args[0]);
			cleanup_paths_bonus(args);
			exit(EXIT_FAILURE);
		}
		else
		{
			ft_putstr_fd(args[0], 2);
			ft_putendl_fd(": Permission denied", 2);
			cleanup_paths_bonus(args);
			exit(126);
		}
	}
}

void	command_not_found_bonus(char **args)
{
	ft_putstr_fd("pipex: ", 2);
	ft_putstr_fd(args[0], 2);
	ft_putendl_fd(": command not found", 2);
	cleanup_paths_bonus(args);
	exit(127);
}

// void	execute_command_bonus(char *cmd, char **envp)
// {
// 	char	**args;
// 	char	*path_env;
// 	int		not_found;

// 	args = get_command_args_bonus(cmd);
// 	path_env = get_path_env_bonus(envp);
// 	not_found = search_and_execute_bonus(args, path_env, envp);
// 	if (not_found)
// 	{
// 		execute_command_directly_bonus(args, envp);
// 		command_not_found_bonus(args);
// 	}
// }

// void execute_command_bonus(char *cmd, char **envp)
// {
//     char *cmd_path;
//     char **cmd_args;

//     cmd_args = parse_command_bonus(cmd);
//     if (!cmd_args || !cmd_args[0])
// 	{
//         perror("Invalid command");
//         exit(127);
//     }
//     cmd_path = resolve_command(cmd_args[0]);
//     if (!cmd_path)
// 	{
//         perror("Command not found");
//         free(cmd_args);
//         exit(127);
//     }
//     if (execve(cmd_path, cmd_args, envp) == -1)
// 	{
//         perror("Execve failed");
//         free(cmd_path);
//         free(cmd_args);
//         exit(127);
//     }
// }

void	execute_command_bonus(char *cmd, char **envp)
{
	char	*cmd_path;
	char	**cmd_args;

	if (!envp || !envp[0])
	{
		static char *default_env[] = {"PATH=/usr/bin:/bin", NULL};
		envp = default_env;
	}
	cmd_args = parse_command_bonus(cmd);
	if (!cmd_args || !cmd_args[0])
	{
		fprintf(stderr, "pipex: %s: Invalid command\n", cmd);
		if (cmd_args)
			free(cmd_args);
		exit(127);
	}
	cmd_path = resolve_command(cmd_args[0], envp);
	if (!cmd_path)
	{
		fprintf(stderr, "pipex: %s: command not found\n", cmd_args[0]);
		free(cmd_args);
		exit(127);
	}
	if (execve(cmd_path, cmd_args, envp) == -1)
	{
		perror("pipex: Execve failed");
		free(cmd_path);
		free(cmd_args);
		exit(1);
	}
	free(cmd_path);
	free(cmd_args);
}

// void execute_command_bonus(char *cmd, char **envp)
// {
//     char *cmd_path;
//     char **cmd_args;

// 	if (!envp || !envp[0])
//     {
//         static char *default_env[] = {"PATH=/usr/bin:/bin", NULL};
//         envp = default_env;
//     }
//     cmd_args = parse_command_bonus(cmd);
//     if (!cmd_args || !cmd_args[0])
//     {
// 		fprintf(stderr, "pipex: %s: Invalid command\n", cmd);
//         if (cmd_args)
//             free(cmd_args);
//         _exit(127);
//     }
//     cmd_path = resolve_command(cmd_args[0]);
//     if (!cmd_path)
//     {
//         fprintf(stderr, "pipex: %s: ", cmd_args[0]);
// 		fprintf(stderr, "command not found\n");
//         free(cmd_args);
//         _exit(127);
//     }
//     if (execve(cmd_path, cmd_args, envp) == -1)
//     {
//         perror("pipex: Execve failed");
//         free(cmd_path);
//         free(cmd_args);
//         exit(1);
//     }
//     free(cmd_path);
//     free(cmd_args);
// }
