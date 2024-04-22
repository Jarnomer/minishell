/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 18:25:45 by jmertane          #+#    #+#             */
/*   Updated: 2024/04/22 19:04:29 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_quotes(char *content, bool *checker, char delim)
{
	int	quotes;
	int	i;

	i = 0;
	quotes = 0;
	while (content[i])
	{
		if (content[i] == delim)
			quotes++;
		++i;
	}
	// if (delim == SINGLEQUOTE && quotes % 2 != 0)
	if (delim == SINGLEQUOTE)
		*checker = false;
	return (quotes);
}

void	filter_quotes(char *content, char delim, bool *checker, t_shell *ms)
{
	char	*temp;
	int		i;
	int		j;

	temp = safe_trash(content, ALLOCATE, ms);
	i = ft_strlen(content) - 1;
	j = i - count_quotes(content, checker, delim);
	ft_bzero(content, i);
	while (i >= 0)
	{
		if (temp[i] != delim)
			content[j--] = temp[i];
		i--;
	}
}

static char	*opposing_quote(char *input, char delim)
{
	while (*input && *input != delim && !ft_isredirect(delim))
		input++;
	if (input != NULL)
		input++;
	return (input);
}

char	*find_breakpoint(char *input, char delim, int hdoc_flag)
{
	int	quotes;

	quotes = 0;
	while (*input && *input != hdoc_flag
		&& !ft_isspace(*input) && !ft_isredirect(*input))
	{
		if (*input == delim && !ft_isspace(*input))
			quotes++;
		input++;
	}
	if (ft_isredirect(*input))
		return (input);
	else if (quotes == 1)
		return (opposing_quote(input, delim));
	else
		return (input);
}

char	assign_delimiter(char *argv)
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
