/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_misc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 18:26:11 by jmertane          #+#    #+#             */
/*   Updated: 2024/04/14 19:23:09 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isenvp(char *input)
{
	if (!input || *input != '$')
		return (FAILURE);
	else
		return (SUCCESS);
}

int	ft_issyntax(char c)
{
	return (c == '>' || c == '<' || c == '|');
}

int	ft_isspace(char c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}
