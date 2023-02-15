/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwyseur <nwyseur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 10:56:29 by nwyseur           #+#    #+#             */
/*   Updated: 2023/02/15 17:57:45 by nwyseur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

char	*ft_findpath(char **envp)
{
	while (strncmp(*envp, "PATH", 4) != 0)
		envp++;
	return (*envp + 5);
}


void	first_child_process(int file, char **cmd, int *pfd, char **envp)
{
	if (dup2(file, STDIN_FILENO) < 0) //file devient le nouveau STDIN;
		ft_error(ERROR_DUP);
	if (dup2(pfd[1], STDOUT_FILENO) < 0)
		ft_error(ERROR_DUP);
	close(pfd[0]);
	close(file);
}

void	second_child_process(int file, char **cmd, int *pfd, char **envp)
{
	if (dup2(file, STDIN_FILENO) < 0) //file devient le nouveau STDIN;
		ft_error(ERROR_DUP);
	if (dup2(pfd[1], STDOUT_FILENO) < 0)
		ft_error(ERROR_DUP);
	close(pfd[0]);
	close(file);
}


void	ft_pipex(t_pipex pipex, char **argv, char **envp)
{
	char	**cmd;

	if (pipe(pipex.pfd) == -1) // envoyer tout ca dans une fonction pipex;
		ft_error(ERROR_PIPE);
	pipex.pid1 = fork();
	if (pipex.pid1 < 0)
		return (-1);
	else if (pipex.pid1 == 0)
	{
		cmd = ft_split(argv[2], ' ');
		first_child_process(pipex.infd, cmd, pipex.pfd, envp[2]);
		ft_freedbltab(cmd);
	}
	else
	{
		cmd = ft_split(argv[3], ' ');
		second_child_process(cmd, pipex.outfd, pipex.pfd, envp [4]);
		ft_freedbltab(cmd);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;


	if (argc < 5)
		ft_error(ERROR_ARG);
	pipex.infd = open(argv[1], O_RDONLY);
	pipex.outfd = open(argv[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (pipex.infd < 0 || pipex.outfd < 0)
		ft_error(ERROR_OPEN);
	pipex.path = ft_split(ft_findpath(envp), ':');
	ft_pipex(pipex, argc, envp);
}
