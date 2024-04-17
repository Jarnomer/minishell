/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_outfile.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 14:10:32 by jmertane          #+#    #+#             */
/*   Updated: 2024/04/17 18:19:42 by jmertane         ###   ########.fr       */
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

static t_parser	*check_outfiles(t_module *mod, t_shell *ms)
{
	t_parser	*outfile;

	outfile = mod->outfiles;
	while (outfile)
	{
		if (ft_strchr(outfile->content, DOLLAR))
			return (error_occured(outfile, MSG_AMB, ms));
		if (opendir(outfile->content) != NULL)
			return (error_occured(outfile, MSG_FLDR, ms));
		else if (access(outfile->content, F_OK) == SUCCESS
			&& access(outfile->content, W_OK) == FAILURE)
			return (error_occured(outfile, strerror(errno), ms));
		else
			close(read_outfile(outfile->content, outfile->mode));
		outfile = outfile->next;
	}
	return (outfile);
}

int	open_outfile(t_module *mod, t_shell *ms)
{
	t_parser	*last;
	int			len;

	if (check_outfiles(mod, ms) != NULL)
		return (FAILURE);
	len = parser_length(mod->outfiles);
	if (len > FDLMT)
		error_limit(len, ms);
	last = parser_last(mod->outfiles);
	mod->outfd = read_outfile(last->content, last->mode);
	return (mod->outfd);
}
