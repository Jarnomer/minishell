/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_word.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/01 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <expand.h>

t_quote_state	update_quote_state(char c, t_quote_state state)
{
	if (c == '\'' && state == Q_NONE)
		return (Q_SINGLE);
	if (c == '\'' && state == Q_SINGLE)
		return (Q_NONE);
	if (c == '"' && state == Q_NONE)
		return (Q_DOUBLE);
	if (c == '"' && state == Q_DOUBLE)
		return (Q_NONE);
	return (state);
}

bool	is_quote_delimiter(char c, t_quote_state state)
{
	if (c == '\'' && (state == Q_NONE || state == Q_SINGLE))
		return (true);
	if (c == '"' && (state == Q_NONE || state == Q_DOUBLE))
		return (true);
	return (false);
}

static char	*handle_dollar(char *word, size_t *i, char *res, t_shell *shell)
{
	char	*name;
	char	*value;
	size_t	len;

	name = get_var_name(word + *i + 1, &len);
	if (!name)
	{
		res = append_char(res, '$');
		return (res);
	}
	value = expand_var(name, shell);
	res = append_str(res, value);
	free(value);
	free(name);
	*i += len;
	return (res);
}

char	*expand_word(char *word, t_shell *shell)
{
	char			*result;
	t_quote_state	state;
	size_t			i;

	result = safe_strdup("");
	state = Q_NONE;
	i = 0;
	while (word[i])
	{
		if (is_quote(word[i]) && is_quote_delimiter(word[i], state))
			state = update_quote_state(word[i], state);
		else if (word[i] == '$' && state != Q_SINGLE)
			result = handle_dollar(word, &i, result, shell);
		else
			result = append_char(result, word[i]);
		i++;
	}
	return (result);
}
