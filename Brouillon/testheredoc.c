/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testheredoc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwyseur <nwyseur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 15:32:46 by nwyseur           #+#    #+#             */
/*   Updated: 2023/02/21 15:34:47 by nwyseur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdarg.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#include <limits.h>
#include <sys/wait.h>
#include <errno.h>

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
		if (ft_strncmp(buf, argv[2], ft_strlen(argv[2])) == 0)
			break ;
		write(heredoc.infd, buf, ft_strlen(buf));
	}
	ft_initheredoc(&heredoc, ac, argv);
}