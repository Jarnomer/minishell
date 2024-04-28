/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 12:57:07 by jmertane          #+#    #+#             */
/*   Updated: 2024/04/13 13:57:01 by jmertane         ###   ########.fr       */
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

static void	prepare_heredoc(t_parser *hdoc, t_shell *ms)
{
	if (pipe(ms->pipefd) == FAILURE)
		error_fatal(errno, MSG_PIPE, ms);
	safe_strjoin(&hdoc->content, hdoc->content, "\n", ms);
}

static int	read_heredoc(t_parser *hdoc, t_shell *ms)
{
	char	*line;
	char	*eof;
	int		len;
	int		fd;

	prepare_heredoc(hdoc, ms);
	eof = hdoc->content;
	len = ft_strlen(eof);
	while (true)
	{
		ft_putstr_fd("> ", STDOUT_FILENO);
		line = get_next_line(STDIN_FILENO);
		if (!line || !ft_strncmp(line, eof, len))
			break ;
		ft_putstr_fd(line, ms->pipefd[WR_END]);
		free(line);
	}
	fd = dup(ms->pipefd[RD_END]);
	finish_heredoc(&line, ms);
	return (fd);
}

static void	read_heredocs(t_module *mod, t_shell *ms)
{
	t_parser	*infile;
	int			tempfd;

	infile = mod->infiles;
	while (infile)
	{
		if (infile->mode == HEREDOC)
		{
			tempfd = read_heredoc(infile, ms);
			if (tempfd != -1 && infile->next)
				close(tempfd);
			else if (tempfd != -1 && !infile->next)
			{
				mod->infd = dup(tempfd);
				close(tempfd);
				return ;
			}
		}
		infile = infile->next;
	}
}

void	open_heredocs(t_module *mod, t_shell *ms)
{
	while (mod)
	{
		read_heredocs(mod, ms);
		mod = mod->next;
	}
}
