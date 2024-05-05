/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 16:56:34 by jmertane          #+#    #+#             */
/*   Updated: 2024/05/04 11:37:47 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	parser_join(t_parser *prev,
	t_parser *new, t_module *mod, t_shell *ms)
{
	int	mode;

	mode = 0;
	if (!prev || !new)
		return ;
	if (!prev->prev)
		mode = new->mode;
	if (new->meta != DOLLAR && new->mode != -1)
		preview_content(prev, new);
	safe_strjoin(&new->content, prev->content, new->content, ms);
	parser_delone(prev);
	if (mode != 0)
	{
		if (mode == -1)
			mod->command = mod->command->next;
		else if (mode == OUTFILE || mode == APPEND)
			mod->outfiles = mod->outfiles->next;
		else
			mod->infiles = mod->infiles->next;
	}
}

static void	filter_quotes(char *content, t_shell *ms)
{
	char	*temp;
	int		len;

	len = ft_strlen(content) - 1;
	temp = safe_trash(content, ALLOCATE, ms);
	ft_bzero(content, len);
	ft_strlcpy(content, temp + 1, len);
}

void	parse_argv(t_parser *new, t_module *mod, t_shell *ms)
{
	if (new->meta == SINGLEQUOTE || new->meta == DOUBLEQUOTE)
		filter_quotes(new->content, ms);
	if (ft_strchr(new->content, DOLLAR)
		&& new->meta != SINGLEQUOTE
		&& new->mode != HEREDOC)
		parse_envps(new, ms);
	if (new->prev != NULL && new->prev->joinable == true)
		parser_join(new->prev, new, mod, ms);
}

static void	check_joinable(t_parser *new, char *c)
{
	if (!*c)
		return ;
	else if (!ft_isredirect(*c) && !ft_isspace(*c))
		new->joinable = true;
}

char	*parse_input(char *argv, t_parser *new)
{
	char	*delim;

	delim = find_breakpoint(argv);
	if (ft_isspace(*delim) || ft_isredirect(*delim))
		return (delim);
	else if (!ft_ismeta(*argv))
	{
		check_joinable(new, delim);
		return (delim);
	}
	new->meta = *delim;
	if (*delim == SINGLEQUOTE)
		delim = ft_strchr(delim + 1, SINGLEQUOTE) + 1;
	else if (*delim == DOUBLEQUOTE)
		delim = ft_strchr(delim + 1, DOUBLEQUOTE) + 1;
	else if (*delim == DOLLAR)
		delim = find_breakpoint(delim + 1);
	check_joinable(new, delim);
	return (delim);
}
