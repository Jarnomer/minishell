/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 16:56:34 by jmertane          #+#    #+#             */
/*   Updated: 2024/04/27 18:32:51 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	filter_quotes(char *content, t_shell *ms)
{
	char	*temp;
	int		len;

	len = ft_strlen(content) - 1;
	temp = safe_trash(content, ALLOCATE, ms);
	ft_bzero(content, len);
	ft_strlcpy(content, temp + 1, len);
}

void	parse_argv(t_parser *new, t_shell *ms)
{
	if (new->meta == SINGLEQUOTE || new->meta == DOUBLEQUOTE)
		filter_quotes(new->content, ms);
	if (ft_strchr(new->content, DOLLAR)
		&& new->meta != SINGLEQUOTE
		&& new->mode != HEREDOC)
		parse_envps(new, ms);
	if (new->prev != NULL && new->prev->joinable == true)
		parser_join(&new->prev, &new, ms);
}

static void	check_joinable(t_parser *new, char c)
{
	if (c != '\0' && !ft_isredirect(c) && !ft_isspace(c))
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
		check_joinable(new, *(delim + 1));
		return (delim);
	}
	new->meta = *delim;
	if (*delim == SINGLEQUOTE)
		delim = ft_strchr(delim + 1, SINGLEQUOTE) + 1;
	else if (*delim == DOUBLEQUOTE)
		delim = ft_strchr(delim + 1, DOUBLEQUOTE) + 1;
	else if (*delim == DOLLAR)
		delim = find_breakpoint(delim + 1);
	check_joinable(new, *delim);
	return (delim);
}
