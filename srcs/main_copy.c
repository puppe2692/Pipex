/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_copy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwyseur <nwyseur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 10:56:29 by nwyseur           #+#    #+#             */
/*   Updated: 2023/03/01 11:35:47 by nwyseur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	first_child_process(t_pipex *pipex, char **cmd, char **envp)
{
	char	*cmd1;

	if (pipex->infd < 0)
	{
		ft_freedbltab(cmd);
		ft_closepipeint(pipex->pfd[0], pipex->pfd[1]);
		ft_error(ERROR_OPE);
	}
	if (dup2(pipex->infd, STDIN_FILENO) < 0)
		ft_errordup(ERROR_DUP, cmd, pipex, 0);
	if (dup2(pipex->pfd[1], STDOUT_FILENO) < 0)
		ft_errordup(ERROR_DUP, cmd, pipex, 0);
	close(pipex->pfd[0]);
	close(pipex->pfd[1]);
	close(pipex->infd);
	cmd1 = ft_verifpath(pipex, cmd, envp);
	execve(cmd1, cmd, envp);
	if (pipex->test == 1)
		free(cmd1);
	ft_freecmderr(NULL, cmd, pipex);
	ft_error(ERROR_EXECVE);
}

void	second_child_process(t_pipex *pipex, char **cmd, char **envp)
{
	char	*cmd2;

	if (dup2(pipex->pfd[0], STDIN_FILENO) < 0)
		ft_errordup(ERROR_DUP, cmd, pipex, 1);
	if (dup2(pipex->outfd, STDOUT_FILENO) < 0)
		ft_errordup(ERROR_DUP, cmd, pipex, 1);
	close(pipex->pfd[0]);
	close(pipex->pfd[1]);
	close(pipex->outfd);
	cmd2 = ft_verifpath(pipex, cmd, envp);
	execve(cmd2, cmd, envp);
	if (pipex->test == 1)
		free(cmd2);
	ft_freecmderr(NULL, cmd, pipex);
	ft_error(ERROR_EXECVE);
}

void	ft_childistrib(t_pipex *pipex, char *argv, char **envp,
				void (*pf)(t_pipex *, char **, char **))
{
	char	**cmd;

	cmd = ft_split(argv, ' ');
	(*pf)(pipex, cmd, envp);
	ft_freedbltab(cmd);
}

int	ft_pipex(t_pipex *pipex, char **argv, char **envp, int argc)
{
	int		status;

	if (pipe(pipex->pfd) == -1)
		ft_error(ERROR_PIPE);
	pipex->pid1 = fork();
	if (pipex->pid1 < 0)
		ft_error(ERROR_PIPE);
	else if (pipex->pid1 == 0)
		ft_childistrib(pipex, argv[2], envp, &first_child_process);
	close(pipex->infd);
	pipex->pid2 = fork();
	if (pipex->pid2 < 0)
		ft_error(ERROR_PIPE);
	else if (pipex->pid2 == 0)
	{
		pipex->outfd = open(argv[argc - 1], O_CREAT | O_RDWR | O_TRUNC, 0644);
		if (pipex->outfd < 0)
			ft_errorfile(ERROR_OPEN, pipex);
		ft_childistrib(pipex, argv[3], envp, &second_child_process);
	}
	ft_closepipe(pipex);
	waitpid(pipex->pid1, &status, 0);
	waitpid(pipex->pid2, &status, 0);
	return (WEXITSTATUS(status));
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;

	if (argc != 5)
		ft_errorparam(ERROR_ARG);
	pipex.infd = open(argv[1], O_RDONLY);
	pipex.test = 0;
	return (ft_pipex(&pipex, argv, envp, argc));
}
