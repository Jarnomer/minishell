/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_misc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 18:26:11 by jmertane          #+#    #+#             */
/*   Updated: 2024/04/15 16:39:12 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
