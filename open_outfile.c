/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_outfile.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 14:10:32 by jmertane          #+#    #+#             */
/*   Updated: 2024/04/07 20:25:58 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static inline int	read_outfile(char *file, int mode)
{
	if (mode == OUTFILE)
		return (open(file, O_CREAT | O_WRONLY | O_TRUNC, 0644));
	else
		return (open(file, O_CREAT | O_WRONLY | O_APPEND, 0644));
}

int	open_outfile(t_module *mod)
{
	t_parser	*file;

	if (!mod->outfiles)
		return (STDOUT_FILENO);
	file = mod->outfiles;
	if (parser_length(file) < 242)
	{
		while (file)
		{
			mod->outfd = read_outfile(file->content, file->mode);
			if (mod->outfd == -1)
				break ;
			if (file->next && mod->outfd != -1)
				close(mod->outfd);
			file = file->next;
		}
	}
	return (mod->outfd);
}
