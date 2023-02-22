/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_copy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwyseur <nwyseur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 17:55:42 by nwyseur           #+#    #+#             */
/*   Updated: 2023/02/22 15:24:29 by nwyseur          ###   ########.fr       */
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
		str = ft_strnstr(*envp, tofind, ft_strlen(tofind));
		if (str != NULL)
			return (1);
		envp++;
	}
	return (0);
}

int	ft_nopath(char **cmd, char **envp)
{
	char	*cmd1;

	if (!ft_ispath(envp, "PATH"))
	{
		if (ft_strchr(cmd[0], '/') != 0)
		{
			cmd1 = cmd[0];
			if (access(cmd1, F_OK) == 0)
				return (1);
		}
		ft_error(ERROR_NOPATH);
	}
	if (ft_strchr(cmd[0], '/') != 0)
	{
		cmd1 = cmd[0];
		if (access(cmd1, F_OK) == 0)
			return (1);
	}
	return (0);
}

char	*ft_verifpath(t_pipex *pipex, char **cmd, char **envp)
{
	int		i;
	char	*cmd1;
	char	*tmp;

	if (ft_nopath(cmd, envp) == 1)
		return (cmd[0]);
	pipex->path = ft_split(ft_findpath(envp), ':');
	i = 0;
	tmp = ft_strjoin(pipex->path[0], "/");
	cmd1 = ft_strjoin(tmp, cmd[0]);
	free(tmp);
	while (access(cmd1, F_OK) != 0 && pipex->path[++i] != NULL)
	{
		free(cmd1);
		tmp = ft_strjoin(pipex->path[i], "/");
		cmd1 = ft_strjoin(tmp, cmd[0]);
		free(tmp);
	}
	if (pipex->path[i] == NULL)
	{
		ft_freecmderr(cmd1, cmd, pipex);
		ft_error(ERROR_CMD);
	}
	ft_freedbltab(pipex->path);
	return (cmd1);
}
