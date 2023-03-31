/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_management.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwyseur <nwyseur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 15:18:57 by nwyseur           #+#    #+#             */
/*   Updated: 2023/03/01 11:45:22 by nwyseur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	ft_freedbltab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	ft_freecmderr(char *cmd1, char **cmd, t_pipex *pipex)
{
	free(cmd1);
	ft_freedbltab(cmd);
	if (pipex->path != NULL && pipex->test != 1)
		ft_freedbltab(pipex->path);
}

void	ft_errordup(char *error, char **cmd, t_pipex *pipex, int a)
{
	ft_closepipeint(pipex->pfd[0], pipex->pfd[1]);
	if (a == 0)
		close(pipex->infd);
	else if (a == 1)
		close(pipex->outfd);
	ft_freedbltab(cmd);
	perror(error);
	exit(errno);
}
