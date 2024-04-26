/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 18:36:21 by jmertane          #+#    #+#             */
/*   Updated: 2024/04/20 17:56:55 by jmertane         ###   ########.fr       */
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

static int	unclosed_quotes(char *input, char delim)
{
	int	quotes;
	int	i;

	i = 0;
	quotes = 0;
	while (input[i])
	{
		if (input[i] == delim)
			quotes++;
		++i;
	}
	return (quotes % 2);
}

static char	assign_delimiter(char *argv)
{
	char	*single_qt;
	char	*double_qt;

	single_qt = ft_strchr(argv, SINGLEQUOTE);
	double_qt = ft_strchr(argv, DOUBLEQUOTE);
	if ((single_qt && double_qt)
		&& (single_qt > double_qt))
		return (DOUBLEQUOTE);
	else if (single_qt && double_qt)
		return (SINGLEQUOTE);
	else if (double_qt)
		return (DOUBLEQUOTE);
	else if (single_qt)
		return (SINGLEQUOTE);
	else
		return (EMPTY);
}

static int	invalid_redirect(char *input, char delim)
{
	while (ft_strchr(input, delim))
	{
		input = ft_strchr(input, delim);
		if (*(input + 1) == delim)
			input += 2;
		else
			input += 1;
		while (ft_isspace(*input))
			input++;
		if (!*input || ft_isredirect(*input))
			return (FAILURE);
	}
	return (SUCCESS);
}

int	error_syntax(char *input, t_shell *ms)
{
	char	c;

	if (!input || !*input || *(input + ft_strlen(input) - 1) == PIPE)
		return (error_occured("`|'", ms));
	else if (invalid_redirect(input, OUTDIRECT))
		return (error_occured("`>'", ms));
	else if (invalid_redirect(input, INDIRECT))
		return (error_occured("`<'", ms));
	c = assign_delimiter(input);
	if (c == SINGLEQUOTE && unclosed_quotes(input, c))
		return (error_occured("`\''", ms));
	else if (c == DOUBLEQUOTE && unclosed_quotes(input, c))
		return (error_occured("`\"'", ms));
	return (SUCCESS);
}
