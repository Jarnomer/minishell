/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_modules.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 18:36:21 by jmertane          #+#    #+#             */
/*   Updated: 2024/04/04 18:36:22 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	error_occured(int errcode, char *token, t_shell *ms)
{
	error_logger(MSG_SYNX, " ", token);
	ms->excode = errcode;
	return (errcode);
}

static int	invalid_argument(char *input, char c)
{
	int	len;

	if (!input || !*input)
		return (FAILURE);
	len = ft_strlen(input) - 1;
	if (input[0] == c)
		return (FAILURE);
	else if (input[len] == c)
		return (FAILURE);
	else
		return (SUCCESS);
}

int	error_syntax(char *input, char c, t_shell *ms)
{
	if (!input || !*input)
		return (SUCCESS);
	else if (c == '|' && invalid_argument(input, c))
		return (error_occured(ERR_SYNX, "'|'", ms));
	else if (c == '<' && invalid_argument(input, c))
		return (error_occured(ERR_SYNX, "'<'", ms));
	else if (c == '>' && invalid_argument(input, c))
		return (error_occured(ERR_SYNX, "'>'", ms));
	return (SUCCESS);
}
