/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_management.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwyseur <nwyseur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 14:46:35 by nwyseur           #+#    #+#             */
/*   Updated: 2023/02/23 10:28:04 by nwyseur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	ft_error(char *error)
{
	perror(error);
	exit(errno);
}

void	ft_errorfile(char *error, t_pipex *pipex)
{
	ft_closepipeint(pipex->pfd[0], pipex->pfd[1]);
	perror(error);
	exit(errno);
}

void	ft_errorparam(char *error)
{
	perror(error);
	exit(1);
}

void	ft_closepipe(t_pipex *pipex)
{
	close(pipex->pfd[0]);
	close(pipex->pfd[1]);
}

void	ft_closepipeint(int a, int b)
{
	close(a);
	close(b);
}
