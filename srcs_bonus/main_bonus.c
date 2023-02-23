/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwyseur <nwyseur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 10:56:29 by nwyseur           #+#    #+#             */
/*   Updated: 2023/02/23 11:19:08 by nwyseur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

void	first_child_process(t_pipex *pipex, char **cmd, char **envp)
{
	int		pfd[2];
	int		pid;
	char	*cmd1;

	if (pipe(pfd) == -1)
		ft_error(ERROR_PIPE);
	pid = fork();
	if (pid < 0)
		ft_error(ERROR_PIPE);
	else if (pid == 0)
	{
		if (pipex->prevfd < 0)
			ft_errorfile(ERROR_OPE, cmd, pfd);
		if (dup2(pipex->prevfd, STDIN_FILENO) < 0
			|| dup2(pfd[1], STDOUT_FILENO) < 0)
			ft_error(ERROR_DUP);
		ft_closepipethree(pfd[0], pfd[1], pipex->prevfd);
		cmd1 = ft_verifpath(pipex, cmd, envp);
		execve(cmd1, cmd, envp);
		ft_freecmderr(cmd1, cmd, pipex);
		ft_error(ERROR_EXECVE);
	}
	close(pipex->prevfd);
	pipex->prevfd = pfd[0];
	close(pfd[1]);
}

void	last_child_process(t_pipex *pipex, char **cmd, char **envp)
{
	int		pid;
	char	*cmd2;

	pid = fork();
	if (pid < 0)
		ft_error(ERROR_PIPE);
	else if (pid == 0)
	{
		if (dup2(pipex->prevfd, STDIN_FILENO) < 0)
			ft_error(ERROR_DUP);
		if (dup2(pipex->outfd, STDOUT_FILENO) < 0)
			ft_error(ERROR_DUP);
		close(pipex->prevfd);
		close(pipex->outfd);
		cmd2 = ft_verifpath(pipex, cmd, envp);
		if (execve(cmd2, cmd, envp) < 0)
		{
			ft_freecmderr(cmd2, cmd, pipex);
			ft_error(ERROR_EXECVE);
		}
	}
	close(pipex->prevfd);
}

void	ft_childistrib(t_pipex *pipex, char *argv, char **envp,
				void (*pf)(t_pipex *, char **, char **))
{
	char	**cmd;

	cmd = ft_split(argv, ' ');
	(*pf)(pipex, cmd, envp);
	ft_freedbltab(cmd);
}

void	ft_pipex(t_pipex *pipex, int ac, char **argv, char **envp)
{
	int		i;

	i = 0;
	pipex->prevfd = pipex->infd;
	while (i < ac - 3)
	{
		if (i < ac - 4)
			ft_childistrib(pipex, argv[i + 2], envp, &first_child_process);
		else if (i == ac - 4)
		{
			pipex->outfd = open(argv[ac - 1], O_CREAT | O_RDWR | O_TRUNC, 0644);
			if (pipex->outfd < 0)
			{
				close(pipex->prevfd);
				ft_error(ERROR_OPEN);
			}
			ft_childistrib(pipex, argv[i + 2], envp, &last_child_process);
		}
		i++;
	}
	while (wait(NULL) != -1)
		;
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex		pipex;

	if (argc < 5)
		ft_errorparam(ERROR_ARG);
	pipex.ishs = ft_isheredoc(argv);
	if ((pipex.ishs == 1 && argc < 6))
		ft_errorparam(ERROR_ARG);
	if (pipex.ishs == 1)
		ft_heredoc(&pipex, argc, argv, envp);
	else
	{
		pipex.infd = open(argv[1], O_RDONLY);
		//if (pipex.infd < 0)
			//ft_errorfile(ERROR_OPE, argv, argc);
		ft_pipex(&pipex, argc, argv, envp);
		close(pipex.outfd);
	}
}
