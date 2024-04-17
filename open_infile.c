/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_infile.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 14:10:32 by jmertane          #+#    #+#             */
/*   Updated: 2024/04/17 18:10:02 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	error_limit(int len, t_shell *ms)
{
	while (len >= FDLMT)
	{
		error_logger("redirection error: ",
			"cannot duplicate fd: ",
			"Too many open files", ms);
		len--;
	}
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
			tempfd = open_heredoc(infile, ms);
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

static t_parser	*error_occured(t_parser *infile, char *errmsg, t_shell *ms)
{
	error_logger(infile->content, ": ", errmsg, ms);
	return (infile);
}

static t_parser	*check_infiles(t_parser *infile, t_shell *ms)
{
	while (infile)
	{
		if (infile->mode != HEREDOC)
		{
			if (ft_strchr(infile->content, DOLLAR))
				return (error_occured(infile, MSG_AMB, ms));
			if (access(infile->content, F_OK) == FAILURE)
				return (error_occured(infile, strerror(errno), ms));
			else if (access(infile->content, F_OK) == SUCCESS
				&& access(infile->content, R_OK) == FAILURE)
				return (error_occured(infile, strerror(errno), ms));
		}
		infile = infile->next;
	}
	return (infile);
}

int	open_infile(t_module *mod, t_shell *ms)
{
	t_parser	*last;
	int			len;

	read_heredocs(mod, ms);
	if (check_infiles(mod->infiles, ms) != NULL)
		return (FAILURE);
	len = parser_length(mod->infiles);
	if (len > FDLMT)
		error_limit(len, ms);
	if (mod->infd != -1)
		return (mod->infd);
	last = parser_last(mod->infiles);
	mod->infd = open(last->content, O_RDONLY);
	return (mod->infd);
}
