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

static int	error_occured(int errcode, char *errmsg, char *token, t_shell *ms)
{
	error_logger(errmsg, " ", token);
	ms->excode = errcode;
	return (FAILURE);
}

static int	unclosed_quotes(char *input, char c)
{
	int	cnt;
	int	i;

	i = 0;
	cnt = 0;
	while (input[i])
	{
		if (input[i] == c)
			cnt++;
		++i;
	}
	return (cnt % 2);
}

static int	invalid_redirect(char *input, char c)
{
	while (ft_strchr(input, c))
	{
		input = ft_strchr(input, c);
		if (*(input + 1) == c)
			input += 2;
		else
			input += 1;
		if (!*input || ft_issyntax(*input))
			return (FAILURE);
	}
	return (SUCCESS);
}

static int	unclosed_pipes(char *input, char c)
{
	int	len;

	len = ft_strlen(input) - 1;
	if (input[0] == c || input[len] == c)
		return (FAILURE);
	else
		return (SUCCESS);
}

int	error_syntax(char *input, char c, t_shell *ms)
{
	if (c == PIPE && unclosed_pipes(input, PIPE))
		return (error_occured(ERR_SYNX, MSG_SYNX, "`|'", ms));
	else
	{
		if (!input || !*input)
			return (error_occured(ERR_SYNX, MSG_SYNX, "`|'", ms));
		else if (invalid_redirect(input, OUTDIRECT))
			return (error_occured(ERR_SYNX, MSG_SYNX, "`>'", ms));
		else if (invalid_redirect(input, INDIRECT))
			return (error_occured(ERR_SYNX, MSG_SYNX, "`<'", ms));
		else if (ft_strchr(input, SINGLEQUOTE)
			&& unclosed_quotes(input, SINGLEQUOTE))
			return (error_occured(ERR_SYNX, MSG_QUOT, "`\''", ms));
		else if (ft_strchr(input, DOUBLEQUOTE)
			&& unclosed_quotes(input, DOUBLEQUOTE))
			return (error_occured(ERR_SYNX, MSG_QUOT, "`\"'", ms));
	}
	return (SUCCESS);
}
