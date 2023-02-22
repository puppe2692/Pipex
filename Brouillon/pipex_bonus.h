/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwyseur <nwyseur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 11:53:50 by nwyseur           #+#    #+#             */
/*   Updated: 2023/02/22 12:45:44 by nwyseur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

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
# include <errno.h>

# define ERROR_OPE "Open infile Error"
# define ERROR_OPEN "Open outfile Error"
# define ERROR_ARG "Arg Error"
# define ERROR_PIPE "Pipe Error"
# define ERROR_DUP "Dup Error"
# define ERROR_CMD "Cmd Error"
# define ERROR_EXECVE "Execve Error"
# define ERROR_NOPATH "No Path Error"

/* List Structure */

typedef struct s_pipex
{
	int		**pfd;
	pid_t	*pid;
	int		infd;
	int		outfd;
	int		i;
	char	**path;

}	t_pipex;

/* fonctions */
void	ft_pipex(t_pipex *pipex, int argc, char **argv, char **envp);
void	ft_childistrib(t_pipex *pipex, char *argv, char **envp,
			void (*pf)(t_pipex *, char **, char **));
void	first_child_process(t_pipex *pipex, char **cmd, char **envp);
void	mid_child_process(t_pipex *pipex, char **cmd, char **envp);
void	last_child_process(t_pipex *pipex, char **cmd, char **envp);
char	*ft_verifpath(t_pipex *pipex, char **cmd);
char	*ft_findpath(char **envp);
int		ft_ispath(char **envp, char *tofind);

/* fonctions free & error*/
void	ft_error(char *error);
void	ft_freedbltab(char **tab);
void	ft_closepipe(t_pipex *pipex);
void	ft_freecmderr(char *cmd1, char **cmd, t_pipex *pipex);

#endif