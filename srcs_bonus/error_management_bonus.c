/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_management_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwyseur <nwyseur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 14:46:35 by nwyseur           #+#    #+#             */
/*   Updated: 2023/02/23 11:19:50 by nwyseur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

void	ft_error(char *error)
{
	perror(error);
	exit(errno);
}

void	ft_errorfile(char *error, char **cmd, int *pfd)
{
	ft_closepipe(pfd[0], pfd[1]);
	ft_freedbltab(cmd);
	perror(error);
	exit(errno);
}

void	ft_errorparam(char *error)
{
	perror(error);
	exit(1);
}

void	ft_closepipe(int a, int b)
{
	close(a);
	close(b);
}

void	ft_closepipethree(int a, int b, int c)
{
	close(a);
	close(b);
	close(c);
}
