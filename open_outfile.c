/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_outfile.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 14:10:32 by jmertane          #+#    #+#             */
/*   Updated: 2024/04/09 16:00:50 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static inline int	read_outfile(char *file, int mode)
{
	if (mode == OUTFILE)
		return (open(file, O_CREAT | O_WRONLY | O_TRUNC, PERMS));
	else
		return (open(file, O_CREAT | O_WRONLY | O_APPEND, PERMS));
}

static void	create_outfiles(t_module *mod, t_shell *ms)
{
	t_parser	*outfile;
	int			tempfd;

	outfile = mod->outfiles;
	while (outfile)
	{
		tempfd = read_outfile(outfile->content, outfile->mode);
		if (tempfd != -1 && outfile->next)
			close(tempfd);
		else if (tempfd != -1 && !outfile->next)
		{
			mod->outfd = dup(tempfd);
			close(tempfd);
		}
		outfile = outfile->next;
	}
}

static t_parser *error_occured(t_parser *infile, char *errmsg, t_shell *ms)
{
	error_logger(infile->content, ": ", errmsg, ms);
	return (infile);
}

static t_parser	*check_outfiles(t_parser *outfile, t_shell *ms)
{
	while (outfile->next)
	{
		if (opendir(outfile->content) != NULL)
				return (error_occured(outfile, MSG_FLDR, ms));
		else if (access(outfile->content, F_OK) == FAILURE)
				return (error_occured(outfile, strerror(errno), ms));
		else if (access(outfile->content, F_OK) == SUCCESS
			&& access(outfile->content, W_OK) == FAILURE)
				return (error_occured(outfile, strerror(errno), ms));
		outfile = outfile->next;
	}
	return (outfile);
}

static int	verify_outfile(t_module *mod, t_parser *files, t_parser *last)
{
	if (files != NULL)
		return (FAILURE);
	else
	{
		mod->outfd = read_outfile(last->content, last->mode);
		return (mod->outfd);
	}
}

int	open_outfile(t_module *mod, t_shell *ms)
{
	t_parser	*files;
	t_parser	*last;

	if (parser_length(mod->outfiles) > FDLMT)
		error_exit(0, "redirection error", MSG_FDLMT, ms);
	files = check_outfiles(mod->outfiles, ms);
	last = parser_last(mod->outfiles);
	return (verify_outfile(mod, files, last));
}
