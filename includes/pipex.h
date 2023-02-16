/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwyseur <nwyseur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 10:57:35 by nwyseur           #+#    #+#             */
/*   Updated: 2023/02/16 16:25:27 by nwyseur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/libft.h"
# include <string.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdint.h>
# include <stdarg.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <string.h>
# include <stdio.h>
# include <limits.h>
# include <sys/wait.h>


# define ERROR_OPE "Open infile Error"
# define ERROR_OPEN "Open outfile Error"
# define ERROR_ARG "Arg Error"
# define ERROR_PIPE "Pipe Error"
# define ERROR_DUP "Dup Error"
# define ERROR_CMD "Cmd Error"
# define ERROR_EXECVE "Execve Error"

/* List Structure */

typedef struct s_pipex
{
	int		pfd[2];
	pid_t	pid1;
	pid_t	pid2;
	int		infd;
	int		outfd;
	char	**path;

}	t_pipex;

/* fonctions */
// void	child_process(int file, char **cmd, int *pfd, char **envp);
char	*ft_findpath(char **envp);

/* fonctions free & error*/
void	ft_error(char *error);
void	ft_freedbltab(char **tab);
void	ft_closepipe(t_pipex *pipex);

#endif