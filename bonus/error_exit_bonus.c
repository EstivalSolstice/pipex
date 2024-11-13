/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joltmann <joltmann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 21:59:02 by joltmann          #+#    #+#             */
/*   Updated: 2024/11/13 21:59:20 by joltmann         ###   ########.fr       */
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
