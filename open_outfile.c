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

static t_parser	*read_outfiles(t_module *mod, t_shell *ms)
{
	t_parser	*outfile;

	outfile = mod->outfiles;
	while (outfile->next)
	{
		if (opendir(outfile->content) != NULL)
		{
			error_exit(ERR_FILE, outfile->content, MSG_FLDR, ms);
			break ;
		}
		else if (access(outfile->content, F_OK) == FAILURE)
		{
			error_exit(ERR_FILE, outfile->content, strerror(errno), ms);
			break ;
		}
		else if (access(outfile->content, F_OK) == SUCCESS
			&& access(outfile->content, W_OK) == FAILURE)
		{
			error_exit(ERR_FILE, outfile->content, strerror(errno), ms);
			break ;
		}
		outfile = outfile->next;
	}
	return (outfile);
}

int	open_outfile(t_module *mod, t_shell *ms)
{
	t_parser	*file;

	if (!mod->outfiles)
		return (STDOUT_FILENO);
	file = mod->outfiles;
	if (parser_length(file) > FDLMT)
		error_exit(0, "redirection error", MSG_FDLMT, ms);
	file = read_outfiles(mod, ms);
	if (file != parser_last(file))
		return (FAILURE);
	else
		return (read_outfile(file->content, file->mode));
}
