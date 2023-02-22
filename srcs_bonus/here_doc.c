/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwyseur <nwyseur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 11:27:15 by nwyseur           #+#    #+#             */
/*   Updated: 2023/02/22 16:02:38 by nwyseur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

int	ft_isheredoc(char **argv)
{
	if (ft_strncmp(argv[1], "here_doc", 8) == 0)
		return (1);
	else
		return (0);
}

void	ft_initheredoc(t_heredoc *heredoc, int ac, char **argv)
{
	int	i;

	heredoc->hdav = (char **)malloc((ac - 1) * sizeof(char *));
	if (!heredoc->hdav)
		ft_error(ERROR_HEREDOC);
	heredoc->hdav[0] = argv[0];
	heredoc->hdav[1] = "here_doctmp.txt";
	i = 2;
	while (i < ac - 1)
	{
		heredoc->hdav[i] = argv[i + 1];
		i++;
	}
}

void	ft_heredocpipex(t_pipex *pipex, t_heredoc *heredoc, char **envp, int ac)
{
	pipex->infd = open("here_doctmp.txt", O_RDONLY);
	if (pipex->infd < 0)
		ft_error(ERROR_OPE);
	ft_pipex(pipex, ac - 1, heredoc->hdav, envp);
	free(heredoc->hdav);
	close(pipex->outfd);
	unlink("here_doctmp.txt");
}

int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while (s1[i] != '\0' && s2[i] != '\0' && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i] - '\n');
}

void	ft_heredoc(t_pipex *pipex, int ac, char **argv, char **envp)
{
	t_heredoc	heredoc;
	char		*buf;

	heredoc.infd = open("here_doctmp.txt", O_CREAT | O_RDWR | O_TRUNC, 0777);
	if (heredoc.infd < 0)
		ft_error(ERROR_OPEN);
	while (1)
	{
		ft_printf("pipe heredoc> ");
		buf = get_next_line(0);
		if (buf == NULL)
			ft_error(ERROR_HEREDOC);
		if (ft_strcmp(buf, argv[2]) == 0)
			break ;
		write(heredoc.infd, buf, ft_strlen(buf));
		free(buf);
	}
	free(buf);
	close(heredoc.infd);
	ft_initheredoc(&heredoc, ac, argv);
	ft_heredocpipex(pipex, &heredoc, envp, ac);
}
