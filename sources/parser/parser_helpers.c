/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 18:26:11 by jmertane          #+#    #+#             */
/*   Updated: 2024/05/16 20:37:16 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

bool	ft_hasspace(char *argv)
{
	while (*argv && !ft_isspace(*argv))
		argv++;
	if (!*argv)
		return (false);
	return (true);
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
	return (c == '\'' || c == '\"' || c == '$' || c == ':');
}

int	ft_isredirect(char c)
{
	return (c == '>' || c == '<');
}
