/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joltmann <joltmann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 21:31:50 by joltmann          #+#    #+#             */
/*   Updated: 2024/12/18 20:22:52 by joltmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	main(int argc, char **argv, char **envp)
{
	static char	*default_env[] = {"PATH=/usr/bin:/bin", NULL};

	if (argc < 5)
	{
		ft_putstr_fd("Usage: ", 2);
		ft_putstr_fd(argv[0], 2);
		ft_putendl_fd(" infile cmd1 cmd2 ... cmdN outfile", 2);
		return (1);
	}
	if (!envp || !envp[0])
		envp = default_env;
	pipex_bonus(argc, argv, envp);
	return (0);
}
