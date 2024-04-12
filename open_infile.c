/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_infile.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 14:10:32 by jmertane          #+#    #+#             */
/*   Updated: 2024/04/09 19:04:19 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	read_heredocs(t_module *mod, t_shell *ms)
{
	t_parser	*infile;
	int			tempfd;

	infile = mod->infiles;
	while (infile)
	{
		if (infile->mode == HEREDOC)
		{
			tempfd = open_heredoc(infile->content, ms);
			if (tempfd != -1 && infile->next)
				close(tempfd);
			else if (tempfd != -1 && !infile->next)
			{
				mod->infd = dup(tempfd);
				close(tempfd);
			}
		}
		infile = infile->next;
	}
}

static t_parser *error_occured(t_parser *infile, char *errmsg, t_shell *ms)
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

static int	verify_infile(t_module *mod, t_parser *files, t_parser *last)
{
	if (files != NULL)
		return (FAILURE);
	else if (mod->infd != -1)
		return (mod->infd);
	else
	{
		mod->infd = (open(last->content, O_RDONLY));
		return (mod->infd);
	}
}

int	open_infile(t_module *mod, t_shell *ms)
{
	t_parser	*files;
	t_parser	*last;

	if (parser_length(mod->infiles) > FDLMT)
		error_exit(0, "redirection error", MSG_FDLMT, ms);
	read_heredocs(mod, ms);
	files = check_infiles(mod->infiles, ms);
	last = parser_last(mod->infiles);
	return (verify_infile(mod, files, last));
}
