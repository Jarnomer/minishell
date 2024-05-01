/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 18:36:21 by jmertane          #+#    #+#             */
/*   Updated: 2024/04/30 19:16:29 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	error_occured(char *token, t_shell *ms)
{
	char	c;

	c = *(token + 1);
	if (c == SINGLEQUOTE || c == DOUBLEQUOTE)
		error_logger(MSG_QUOT, " ", token, ms);
	else
		error_logger(MSG_SYNX, " ", token, ms);
	ms->excode = ERR_SYNX;
	return (FAILURE);
}

static char	assign_delimiter(char *argv)
{
	char	*single_qt;
	char	*double_qt;

	single_qt = ft_strchr(argv, SINGLEQUOTE);
	double_qt = ft_strchr(argv, DOUBLEQUOTE);
	if (!single_qt && !double_qt)
		return (0);
	else if ((single_qt && double_qt)
		&& (single_qt > double_qt))
		return (DOUBLEQUOTE);
	else if (single_qt && double_qt)
		return (SINGLEQUOTE);
	else if (double_qt)
		return (DOUBLEQUOTE);
	else
		return (SINGLEQUOTE);
}

static int	unclosed_quotes(char *input)
{
	char	delim;

	while (input)
	{
		delim = assign_delimiter(input);
		if (!delim)
			return (SUCCESS);
		input = ft_strchr(input, delim);
		if (!ft_strchr(input + 1, delim))
			return (delim);
		input = ft_strchr(input + 1, delim) + 1;
	}
	return (SUCCESS);
}

static int	invalid_redirect(char *input, char redirect)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] == '$' || (!ft_ismeta(input[i]) && !ft_isredirect(input[i])))
			i++;
		else if (ft_ismeta(input[i]))
		{
			i++;
			while (input[i] && input[i] != SINGLEQUOTE && input[i] != DOUBLEQUOTE)
				i++;
			i++;
		}
		else
		{
			if (input[i + 1] == redirect)
				i += 2;
			else
				i += 1;
			while (ft_isspace(input[i]))
				i++;
			if (!input[i] || ft_isredirect(input[i]))
				return (FAILURE);
		}
	}
	return (SUCCESS);
}

int	error_syntax(char *input, t_shell *ms)
{
	char	quote;

	if (!input || !*input || *input == PIPE
		|| *(input + ft_strlen(input) - 1) == PIPE)
		return (error_occured("`|'", ms));
	quote = unclosed_quotes(input);
	if (quote == SINGLEQUOTE)
		return (error_occured("`\''", ms));
	else if (quote == DOUBLEQUOTE)
		return (error_occured("`\"'", ms));
	else if (invalid_redirect(input, OUTDIRECT))
		return (error_occured("`>'", ms));
	else if (invalid_redirect(input, INDIRECT))
		return (error_occured("`<'", ms));
	return (SUCCESS);
}
