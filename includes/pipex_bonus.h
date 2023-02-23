/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwyseur <nwyseur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 11:53:50 by nwyseur           #+#    #+#             */
/*   Updated: 2023/02/23 11:20:01 by nwyseur          ###   ########.fr       */
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
# define ERROR_PID "Pid Error"
# define ERROR_DUP "Dup Error"
# define ERROR_CMD "Cmd Error"
# define ERROR_EXECVE "Execve Error"
# define ERROR_NOPATH "No Path Error"
# define ERROR_HEREDOC "Here_doc Error"

/* List Structure */

typedef struct s_pipex
{
	int		infd;
	int		outfd;
	int		i;
	int		prevfd;
	int		ishs;
	char	**path;
}	t_pipex;

typedef struct s_heredoc
{
	char	**hdav;
	int		infd;
}	t_heredoc;

/* fonctions */
void	ft_pipex(t_pipex *pipex, int ac, char **argv, char **envp);
void	ft_childistrib(t_pipex *pipex, char *argv, char **envp,
			void (*pf)(t_pipex *, char **, char **));
void	first_child_process(t_pipex *pipex, char **cmd, char **envp);
void	second_child_process(t_pipex *pipex, char **cmd, char **envp);
char	*ft_verifpath(t_pipex *pipex, char **cmd, char **envp);
char	*ft_findpath(char **envp);
int		ft_ispath(char **envp, char *tofind);
int		ft_nopath(char **cmd, char **envp);

/* fonctions here_doc*/
int		ft_isheredoc(char **argv);
void	ft_initheredoc(t_heredoc *heredoc, int ac, char **argv);
void	ft_heredoc(t_pipex *pipex, int ac, char **argv, char **envp);
void	ft_heredocpipex(t_pipex *pipex, t_heredoc *heredoc,
			char **envp, int ac);
int		ft_strcmp(const char *s1, const char *s2);

/* fonctions free & error*/
void	ft_error(char *error);
void	ft_errorparam(char *error);
void	ft_errorfile(char *error, char **cmd, int *pfd);
void	ft_freedbltab(char **tab);
void	ft_closepipe(int a, int b);
void	ft_closepipethree(int a, int b, int c);
void	ft_freecmderr(char *cmd1, char **cmd, t_pipex *pipex);

#endif