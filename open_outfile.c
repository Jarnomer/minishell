/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_outfile.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 14:10:32 by jmertane          #+#    #+#             */
/*   Updated: 2024/04/13 13:56:08 by jmertane         ###   ########.fr       */
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

static inline int	read_outfile(char *file, int mode)
{
	if (mode == OUTFILE)
		return (open(file, O_CREAT | O_WRONLY | O_TRUNC, PERMS));
	else
		return (open(file, O_CREAT | O_WRONLY | O_APPEND, PERMS));
}

static t_parser	*error_occured(t_parser *outfile, char *errmsg, t_shell *ms)
{
	error_logger(outfile->content, ": ", errmsg, ms);
	return (outfile);
}

static t_parser	*check_outfiles(t_parser *outfile, t_shell *ms)
{
	while (outfile)
	{
		if (opendir(outfile->content) != NULL)
			return (error_occured(outfile, MSG_FLDR, ms));
		else if (access(outfile->content, F_OK) == SUCCESS
			&& access(outfile->content, W_OK) == FAILURE)
			return (error_occured(outfile, strerror(errno), ms));
		outfile = outfile->next;
	}
	return (outfile);
}

int	open_outfile(t_module *mod, t_shell *ms)
{
	t_parser	*files;
	t_parser	*last;
	int			len;

	files = check_outfiles(mod->outfiles, ms);
	if (files != NULL)
		return (FAILURE);
	len = parser_length(mod->outfiles);
	if (len > FDLMT)
		error_limit(len, ms);
	last = parser_last(mod->outfiles);
	mod->outfd = read_outfile(last->content, last->mode);
	return (mod->outfd);
}
