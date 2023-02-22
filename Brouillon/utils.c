/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwyseur <nwyseur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 17:55:42 by nwyseur           #+#    #+#             */
/*   Updated: 2023/02/22 11:32:05 by nwyseur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

char	*ft_findpath(char **envp)
{
	while (ft_strncmp(*envp, "PATH=", 5) != 0)
		envp++;
	return (*envp + 5);
}

int	ft_ispath(char **envp, char *tofind)
{
	int		i;
	char	*str;

	i = 0;
	str = NULL;
	while (envp != NULL && *envp != NULL)
	{
		str = ft_strnstr(*envp, tofind, 4);
		if (str != NULL)
			return (1);
		envp++;
	}
	return (0);
}

char	*ft_verifpath(t_pipex *pipex, char **cmd)
{
	int		i;
	char	*cmd1;
	char	*tmp;

	tmp = ft_strjoin(pipex->path[0], "/");
	cmd1 = ft_strjoin(tmp, cmd[0]);
	free(tmp);
	i = 1;
	while (access(cmd1, F_OK) != 0 && pipex->path[i] != NULL)
	{
		free(cmd1);
		tmp = ft_strjoin(pipex->path[i], "/");
		cmd1 = ft_strjoin(tmp, cmd[0]);
		free(tmp);
		i++;
	}
	if (pipex->path[i] == NULL)
	{
		ft_freecmderr(cmd1, cmd, pipex);
		ft_error(ERROR_CMD);
	}
	return (cmd1);
}
