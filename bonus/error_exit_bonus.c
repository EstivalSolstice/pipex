/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_exit_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joltmann <joltmann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 21:59:02 by joltmann          #+#    #+#             */
/*   Updated: 2024/11/30 21:25:59 by joltmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	error_exit_bonus(const char *msg)
{
	ft_putstr_fd("pipex: ", 2);
	ft_putendl_fd((char *)msg, 2);
	exit(EXIT_FAILURE);
}

void	infile_error_exit_bonus(const char *filename)
{
	ft_putstr_fd("pipex: ", 2);
	perror(filename);
	exit(0);
}
