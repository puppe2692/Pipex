/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwyseur <nwyseur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 10:56:29 by nwyseur           #+#    #+#             */
/*   Updated: 2023/02/16 16:26:38 by nwyseur          ###   ########.fr       */
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


void	first_child_process(t_pipex *pipex, char **cmd, char **envp)
{
	char	*cmd1;

	if (dup2(pipex->infd, STDIN_FILENO) < 0)
		ft_error(ERROR_DUP);
	if (dup2(pipex->pfd[1], STDOUT_FILENO) < 0)
		ft_error(ERROR_DUP);
	close(pipex->pfd[0]);
	close(pipex->infd);
	cmd1 = ft_verifpath(pipex, cmd);
	if (execve(cmd1, cmd, envp) < 0)
		ft_error(ERROR_EXECVE);
}

void	second_child_process(t_pipex *pipex, char **cmd, char **envp)
{
	char	*cmd2;

	if (dup2(pipex->pfd[0], STDIN_FILENO) < 0)
		ft_error(ERROR_DUP);
	if (dup2(pipex->outfd, STDOUT_FILENO) < 0)
		ft_error(ERROR_DUP);
	close(pipex->pfd[1]);
	close(pipex->outfd);
	cmd2 = ft_verifpath(pipex, cmd);
	if (execve(cmd2, cmd, envp) < 0)
		ft_error(ERROR_EXECVE);
}


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
	pipex.path = ft_split(ft_findpath(envp), ':');
	ft_pipex(&pipex, argv, envp);
}
