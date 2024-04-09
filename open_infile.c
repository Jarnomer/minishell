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

static t_parser	*read_heredocs(t_parser	*file, int *infd, t_shell *ms)
{
	printf("Started reading heredocs\n");
	while (file->next)
	{
		printf("Filemode is: %d\n", file->mode);
		if (file->mode == HEREDOC)
		{
			printf("Detected heredoc!\n");
			*infd = open_heredoc(file->content, ms);
			if (*infd != -1 && file->next != NULL)
				close(*infd);
		}
		file = file->next;
	}
	return (file);
}

static t_parser	*read_infiles(t_module *mod, t_shell *ms)
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
			error_exit(ERR_FILE, infile->content, strerror(errno), ms);
			break ;
		}
		else if (access(infile->content, F_OK) == SUCCESS
			&& access(infile->content, R_OK) == FAILURE)
		{
			error_exit(ERR_FILE, infile->content, strerror(errno), ms);
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

	if (!mod->infiles)
		return (STDIN_FILENO);
	file = mod->infiles;
	if (parser_length(file) > FDLMT)
		error_exit(0, "redirection error", MSG_FDLMT, ms);
	last = read_heredocs(file, &infd, ms);
	file = read_infiles(mod, ms);
	if (file != last)
		return (FAILURE);
	else if (last->mode == INFILE)
		return (open(file->content, O_RDONLY));
	else
		return (infd);
}
