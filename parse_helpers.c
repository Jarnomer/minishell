/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 18:25:45 by jmertane          #+#    #+#             */
/*   Updated: 2024/04/14 13:32:31 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_quotes(char *content, bool *checker, char c)
{
	int	cnt;
	int	i;

	i = 0;
	cnt = 0;
	while (content[i])
	{
		if (content[i] == c)
			cnt++;
		++i;
	}
	if (cnt % 2 != 0 && c == SINGLEQUOTE)
		*checker = false;
	// printf("cnt is %d result %d checker %d\n", cnt, (cnt / 2) % 2, *checker);
	return (cnt);
}

void	filter_quotes(char *content, char c, bool *checker, t_shell *ms)
{
	char	*temp;
	int		i;
	int		j;

	safe_strdup(&temp, content, ms);
	i = ft_strlen(content) - 1;
	j = i - count_quotes(content, checker, c);
	ft_bzero(content, i);
	while (i >= 0)
	{
		if (temp[i] != c)
			content[j--] = temp[i];
		i--;
	}
	free(temp);
}

static char	*opposing_quote(char *input, char c)
{
	while (*input && *input != c && !ft_isredirect(c))
		input++;
	return (++input);
}

char	*find_breakpoint(char *input, char c, int hdoc_flag)
{
	int	quotes;

	quotes = 0;
	if (*input == '$')
		input++;
	while (*input && *input != hdoc_flag
		&& !ft_isspace(*input) && !ft_isredirect(*input))
	{
		if (*input == c && !ft_isspace(*input))
			quotes++;
		input++;
	}
	if (ft_isredirect(*input))
		return (input);
	else if (quotes == 1)
		return (opposing_quote(input, c));
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
