/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_outfile.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 14:10:32 by jmertane          #+#    #+#             */
/*   Updated: 2024/05/09 19:04:37 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	read_outfile(char *file, int mode)
{
	if (mode == OUTFILE)
		return (open(file, O_CREAT | O_WRONLY | O_TRUNC, PERMS));
	else
		return (open(file, O_CREAT | O_WRONLY | O_APPEND, PERMS));
}

static int	error_occured(t_parser *outfile, char *errmsg, t_shell *ms)
{
	error_logger(outfile->content, ": ", errmsg, ms);
	return (-1);
}

static int	directory_exists(char *content, t_shell *ms)
{
	char	*folder;
	char	*end;
	int		len;

	end = ft_strrchr(content, '/');
	len = ft_strlen(content) - ft_strlen(end);
	folder = safe_trash(ft_substr(content, 0, len), ALLOCATED, ms);
	if (opendir(folder) == NULL)
		return (-1);
	return (0);
}

static int	check_outfile(t_parser *outfile, t_shell *ms)
{
	if (*outfile->content == DOLLAR && outfile->meta != SINGLEQUOTE)
		return (error_occured(outfile, MSG_AMB, ms));
	else if (opendir(outfile->content) != NULL)
		return (error_occured(outfile, MSG_FLDR, ms));
	else if (ft_strchr(outfile->content, '/')
		&& directory_exists(outfile->content, ms) == -1)
		return (error_occured(outfile, MSG_FILE, ms));
	else if (access(outfile->content, F_OK) == 0
		&& access(outfile->content, W_OK) == -1)
		return (error_occured(outfile, MSG_PERM, ms));
	return (0);
}

t_parser	*open_outfile(t_parser *outfile, t_module *mod, t_shell *ms)
{
	if (check_outfile(outfile, ms) == -1)
		return (NULL);
	if (outfile->next != NULL)
	{
		close(read_outfile(outfile->content, outfile->mode));
		return (outfile->next);
	}
	mod->outfd = read_outfile(outfile->content, outfile->mode);
	return (outfile);
}
