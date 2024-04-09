/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_outfile.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 14:10:32 by jmertane          #+#    #+#             */
/*   Updated: 2024/04/08 20:28:59 by jmertane         ###   ########.fr       */
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

static t_parser	*read_outfiles(t_module *mod)
{
	t_parser	*outfile;

	outfile = mod->outfiles;
	while (outfile->next)
	{
		if (opendir(outfile->content) != NULL)
		{
			error_child(outfile->content, MSG_FLDR, mod);
			break ;
		}
		else if (access(outfile->content, F_OK) == FAILURE)
		{
			error_child(outfile->content, strerror(errno), mod);
			break ;
		}
		else if (access(outfile->content, F_OK) == SUCCESS
			&& access(outfile->content, W_OK) == FAILURE)
		{
			error_child(outfile->content, strerror(errno), mod);
			break ;
		}
		outfile = outfile->next;
	}
	return (outfile);
}

int	open_outfile(t_module *mod)
{
	t_parser	*file;

	if (parser_length(mod->outfiles) > FDLMT)
		return (FAILURE);
	file = read_outfiles(mod);
	if (file != parser_last(file))
		return (FAILURE);
	else
		return (read_outfile(file->content, file->mode));
}
