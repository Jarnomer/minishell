/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 18:26:11 by jmertane          #+#    #+#             */
/*   Updated: 2024/04/30 19:20:07 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	reformat_content(t_parser *prev, t_parser *new)
{
	if (*prev->content == DOLLAR
		&& new->meta != DOLLAR)
		ft_bzero(prev->content, ft_strlen(prev->content));
	else if (*prev->content != DOLLAR
		&& ft_strlen(new->content) != 1
		&& ft_strchr(new->content, DOLLAR)
		&& new->meta != SINGLEQUOTE)
		ft_bzero(new->content, ft_strlen(new->content));
}

char	*find_breakpoint(char *argv)
{
	while (*argv != '\0'
		&& !ft_ismeta(*argv)
		&& !ft_isredirect(*argv)
		&& !ft_isspace(*argv))
		argv++;
	return (argv);
}

int	ft_ismeta(char c)
{
	return (c == '\'' || c == '\"' || c == '$');
}

int	ft_isredirect(char c)
{
	return (c == '>' || c == '<');
}

int	ft_isspace(char c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}
