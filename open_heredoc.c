/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 12:57:07 by jmertane          #+#    #+#             */
/*   Updated: 2024/04/09 16:18:31 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	finish_heredoc(char **line, t_shell *ms)
{
	get_next_line(-1);
	free_single(line);
	close(ms->pipefd[WR_END]);
	close(ms->pipefd[RD_END]);
}

static int	prepare_heredoc(char *eof, t_shell *ms)
{
	printf("Creating pipe to read hdoc\n");
	if (pipe(ms->pipefd) == FAILURE)
		perror(MSG_PIPE);
		// error_fatal(errno, MSG_PIPE, ms);
	safe_strjoin(&eof, eof, "\n", ms);
	ft_putstr_fd("> ", STDOUT_FILENO);
	return (ft_strlen(eof));
}

int	open_heredoc(char *eof, t_shell *ms)
{
	char	*line;
	int		len;
	int		fd;

	len = prepare_heredoc(eof, ms);
	while (true)
	{
		printf("Reading first heredoc\n");
		line = get_next_line(STDIN_FILENO);
		if (!line)
			break ;
		if (!ft_strncmp(line, eof, len))
			break ;
		ft_putstr_fd(line, ms->pipefd[WR_END]);
		free(line);
	}
	fd = dup(ms->pipefd[RD_END]);
	finish_heredoc(&line, ms);
	return (fd);
}
