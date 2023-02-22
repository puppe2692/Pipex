/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_management_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwyseur <nwyseur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 14:46:35 by nwyseur           #+#    #+#             */
/*   Updated: 2023/02/22 16:29:38 by nwyseur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

void	ft_error(char *error)
{
	perror(error);
	exit(errno);
}

void	ft_errorfile(char *error, char **argv, int argc)
{
	int	i;

	perror(error);
	i = open(argv[argc - 1], O_CREAT | O_RDWR | O_TRUNC, 0777);
	if (i < 0)
		ft_error(ERROR_OPEN);
	else
	{
		close(i);
		exit(errno);
	}
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
