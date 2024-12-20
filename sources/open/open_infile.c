/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_infile.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 14:10:32 by jmertane          #+#    #+#             */
/*   Updated: 2024/05/05 15:53:58 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	error_occured(t_parser *infile, char *errmsg, t_shell *ms)
{
	error_logger(infile->content, ": ", errmsg, ms);
	return (-1);
}

static int	check_infile(t_parser *infile, t_shell *ms)
{
	if (infile->mode == HEREDOC)
		return (0);
	else if (*infile->content == DOLLAR && infile->meta != SINGLEQUOTE
		&& ft_strlen(infile->content) != 1)
		return (error_occured(infile, MSG_AMB, ms));
	else if (access(infile->content, F_OK) == -1)
		return (error_occured(infile, MSG_FILE, ms));
	else if (access(infile->content, F_OK) == 0
		&& access(infile->content, R_OK) == -1)
		return (error_occured(infile, MSG_PERM, ms));
	return (0);
}

t_parser	*open_infile(t_parser *infile, t_module *mod, t_shell *ms)
{
	while (infile->next && infile->mode == HEREDOC)
		infile = infile->next;
	if (check_infile(infile, ms) == -1)
		return (NULL);
	else if (infile->next != NULL)
		return (infile->next);
	else if (infile->mode == HEREDOC)
		return (infile);
	mod->infd = open(infile->content, O_RDONLY);
	return (infile);
}
