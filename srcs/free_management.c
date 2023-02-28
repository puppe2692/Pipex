/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_management.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwyseur <nwyseur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 15:18:57 by nwyseur           #+#    #+#             */
/*   Updated: 2023/02/28 17:28:20 by nwyseur          ###   ########.fr       */
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
	(void) pipex;
	if (pipex->path != NULL && pipex->test != 1)
		ft_freedbltab(pipex->path);
}
