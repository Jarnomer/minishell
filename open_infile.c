/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_infile.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 14:10:32 by jmertane          #+#    #+#             */
/*   Updated: 2024/04/08 20:29:05 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_parser	*read_heredocs(t_parser	*file, int *infd, t_shell *ms)
{
	while (file->next)
	{
		if (file->mode == HEREDOC)
		{
			*infd = open_heredoc(file->content, ms);
			if (*infd != -1 && file->next != NULL)
				close(*infd);
		}
		file = file->next;
	}
	return (file);
}

static t_parser	*read_infiles(t_module *mod)
{
	t_parser	*infile;

	infile = mod->infiles;
	while (infile->next)
	{
		if (infile->mode == HEREDOC)
		{
			infile = infile->next;
			continue ;
		}
		else if (access(infile->content, F_OK) == FAILURE)
		{
			error_child(infile->content, MSG_FILE, mod);
			break ;
		}
		else if (access(infile->content, F_OK) == SUCCESS
			&& access(infile->content, R_OK) == FAILURE)
		{
			error_child(infile->content, MSG_PERM, mod);
			break ;
		}
		infile = infile->next;
	}
	return (infile);
}

int	open_infile(t_module *mod, t_shell *ms)
{
	t_parser	*file;
	t_parser	*last;
	int			infd;

	file = mod->infiles;
	if (parser_length(mod->infiles) > FDLMT)
		return (FAILURE);
	last = read_heredocs(file, &infd, ms);
	file = read_infiles(mod);
	if (file != last)
		return (FAILURE);
	else if (last->mode == INFILE)
		return (open(file->content, O_RDONLY));
	else
		return (infd);
}
