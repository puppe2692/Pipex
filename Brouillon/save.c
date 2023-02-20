/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwyseur <nwyseur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 18:04:01 by nwyseur           #+#    #+#             */
/*   Updated: 2023/02/20 16:52:48 by nwyseur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	ft_pipex(t_pipex *pipex, char **argv, char **envp)
{
	char	**cmd;
	int		status;

	if (pipe(pipex->pfd) == -1)
		ft_error(ERROR_PIPE);
	pipex->pid1 = fork();
	if (pipex->pid1 < 0)
		ft_error(ERROR_PIPE);
	else if (pipex->pid1 == 0)
	{
		cmd = ft_split(argv[2], ' ');
		first_child_process(pipex, cmd, envp);
		ft_freedbltab(cmd);
	}
	pipex->pid2 = fork();
	if (pipex->pid2 < 0)
		ft_error(ERROR_PIPE);
	else if (pipex->pid2 == 0)
	{
		cmd = ft_split(argv[3], ' ');
		second_child_process(pipex, cmd, envp);
		ft_freedbltab(cmd);
	}
	ft_closepipe(pipex);
	waitpid(pipex->pid1, &status, 0);
	waitpid(pipex->pid2, &status, 0);
}


		pipex->pid[i] = fork();
		if (pipex->pid[i] < 0)
			ft_error(ERROR_PIPE);

				else if (pipex->pid[i] == 0)