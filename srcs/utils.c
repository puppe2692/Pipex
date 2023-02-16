/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwyseur <nwyseur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 17:55:42 by nwyseur           #+#    #+#             */
/*   Updated: 2023/02/16 18:29:52 by nwyseur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

char	*ft_findpath(char **envp)
{
	while (strncmp(*envp, "PATH", 4) != 0)
		envp++;
	return (*envp + 5);
}

char	*ft_verifpath(t_pipex *pipex, char **cmd)
{
	int		i;
	char	*cmd1;
	char	*tmp;

	tmp = ft_strjoin(pipex->path[0], "/");
	cmd1 = ft_strjoin(tmp, cmd[0]);
	i = 1;
	while (access(cmd1, F_OK) != 0 && pipex->path[i] != NULL)
	{
		tmp = ft_strjoin(pipex->path[i], "/");
		cmd1 = ft_strjoin(tmp, cmd[0]);
		i++;
	}
	if (pipex->path[i] == NULL)
		ft_error(ERROR_CMD);
	return (cmd1);
}
