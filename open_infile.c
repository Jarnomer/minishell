/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_infile.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 14:10:32 by jmertane          #+#    #+#             */
/*   Updated: 2024/04/07 20:27:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error_child(char *s1, char *s2, t_module *mod)
{
	mod->errmsg[0] = s1;
	mod->errmsg[1]= ": ";
	mod->errmsg[2] = s2;
}

static void	pseudo_read_hdoc(t_parser	*file, t_shell *ms)
{
	int	fd;

	while (file->next)
	{
		if (file->mode == HEREDOC)
		{
			fd = open_heredoc(file->content, ms);
			if (fd != -1)
				close(fd);
		}
		file = file->next;
	}
}

static t_parser	*process_infiles(t_module *mod)
{
	t_parser	*file;
	char		*filename;

	file = mod->infiles;
	while (file->next)
	{
		filename = file->content;
		if (file->mod == HEREDOC)
		{
			pseudo_read_hdoc(file, ms);
			file = file->next;
			continue ;
		}
		else if (access(filename, F_OK) == FAILURE)
		{
			error_child(filename, MSG_FILE, mod);
			break ;
		}
		else if (access(filename, F_OK) == SUCCESS
			&& access(filename, R_OK) == FAILURE)
		{
			error_child(filename, MSG_PERM, mod);
			break ;
		}
		file = file->next;
	}
	return (file);
}

int	open_infile(t_module *mod, t_shell *ms)
{
	t_parser	*file;
	int			infd;

	if (!mod->infiles)
		return (STDIN_FILENO);
	if (parser_length(file) > 241)
		return (FAILURE); // fatal error
	file = process_infiles(mod);
	if (file->next != NULL)
		pseudo_read_hdoc(file, ms);
	if (file->next != NULL)
		return (FAILURE);
	else if (file->mode == HEREDOC)
		infd = open_heredoc(file->content, ms);
	else
		infd = open(file->content, O_RDONLY);
	return (infd);
}
