/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   falsemain_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwyseur <nwyseur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 10:56:29 by nwyseur           #+#    #+#             */
/*   Updated: 2023/02/20 16:24:48 by nwyseur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

void	first_child_process(t_pipex *pipex, char **cmd, char **envp)
{
	char	*cmd1;

	if (dup2(pipex->infd, STDIN_FILENO) < 0)
		ft_error(ERROR_DUP);
	if (dup2(pipex->pfd[0][1], STDOUT_FILENO) < 0)
		ft_error(ERROR_DUP);
	close(pipex->pfd[0]);
	close(pipex->infd);
	cmd1 = ft_verifpath(pipex, cmd);
	if (execve(cmd1, cmd, envp) < 0)
	{
		ft_freecmderr(cmd1, cmd, pipex);
		ft_error(ERROR_EXECVE);
	}
}

void	mid_child_process(t_pipex *pipex, char **cmd, char **envp)
{
	char	*cmd1;

	if (dup2(pipex->pfd[pipex->i - 1][0], STDIN_FILENO) < 0)
		ft_error(ERROR_DUP);
	if (dup2(pipex->pfd[pipex->i][1], STDOUT_FILENO) < 0)
		ft_error(ERROR_DUP);
	close(pipex->pfd[pipex->i - 1][1]);
	close(pipex->pfd[pipex->i][0]);
	cmd1 = ft_verifpath(pipex, cmd);
	if (execve(cmd1, cmd, envp) < 0)
	{
		ft_freecmderr(cmd1, cmd, pipex);
		ft_error(ERROR_EXECVE);
	}
}

void	last_child_process(t_pipex *pipex, char **cmd, char **envp)
{
	char	*cmd1;

	if (dup2(pipex->pfd[pipex->i - 1][0], STDIN_FILENO) < 0)
		ft_error(ERROR_DUP);
	if (dup2(pipex->outfd, STDOUT_FILENO) < 0)
		ft_error(ERROR_DUP);
	close(pipex->pfd[1]);
	close(pipex->outfd);
	cmd1 = ft_verifpath(pipex, cmd);
	if (execve(cmd1, cmd, envp) < 0)
	{
		ft_freecmderr(cmd1, cmd, pipex);
		ft_error(ERROR_EXECVE);
	}
}

void	ft_pipex(t_pipex *pipex, int ac, char **argv, char **envp)
{
	int		status;
	int		i;

	ft_initpid(pipex, ac);
	i = 0;
	while (i < ac - 3)
	{
		pipex->i = i;
		pipex->pid[i] = fork();
		if (pipex->pid[i] < 0)
			ft_error(ERROR_PIPE);
		else if (pipex->pid[i] == 0)
		{
			if (i == 0)
				ft_childistrib(pipex, argv[2], envp, &first_child_process);
			else if (i == ac - 4)
				ft_childistrib(pipex, argv[ac - 2], envp, &last_child_process);
			else
				ft_childistrib(pipex, argv[i + 2], envp, &mid_child_process);
		}
	}
	ft_closepipe(pipex);
	waitpid(pipex->pid1, &status, 0);
	waitpid(pipex->pid2, &status, 0);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;

	if (argc < 5)
		ft_error(ERROR_ARG);
	pipex.infd = open("file1", O_RDONLY);
	if (pipex.infd < 0)
		ft_error(ERROR_OPE);
	pipex.outfd = open("file2", O_CREAT | O_RDWR | O_TRUNC, 0777);
	if (pipex.outfd < 0)
		ft_error(ERROR_OPEN);
	if (!ft_ispath(envp, "PATH"))
		ft_error(ERROR_NOPATH);
	pipex.path = ft_split(ft_findpath(envp), ':');
	ft_pipex(&pipex, argc, argv, envp);
	ft_freedbltab(pipex.path);
}
