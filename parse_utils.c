#include "minishell.h"

static int	count_quotes(char *content, char c)
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
	return (cnt);
}

void	filter_quotes(char *content, char c, t_shell *ms)
{
	char	*temp;
	int		i;
	int		j;

	safe_strdup(&temp, content, ms);
	i = ft_strlen(content) - 1;
	j = i - count_quotes(content, c);
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
	// need to add syntax error handling for unclosed quotes
	while (*input && *input != c && !ft_issyntax(c))
		input++;
	return (++input);
}

char	*find_breakpoint(char *input, char c)
{
	int	quotes;

	quotes = 0;
	while (*input && !ft_isspace(*input) && !ft_issyntax(*input))
	{
		if (*input == c && !ft_isspace(*input))
			quotes++;
		input++;
	}
	if (ft_issyntax(*input))
		return (input);
	else if (quotes == 1)
		return (opposing_quote(input, c));
	else
		return (input);
}

char	assign_delimiter(char *argv)
{
	char	*sngl;
	char	*dpbl;

	sngl = ft_strchr(argv, '\'');
	dpbl = ft_strchr(argv, '\"');
	if ((sngl && dpbl) && (sngl > dpbl))
		return ('\"');
	else if (sngl && dpbl)
		return ('\'');
	else if (dpbl)
		return ('\"');
	else if (sngl)
		return ('\'');
	else
		return (' ');
}
