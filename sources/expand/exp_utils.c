/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/01 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <expand.h>

char	*append_char(char *result, char c)
{
	char	str[2];
	char	*new;

	str[0] = c;
	str[1] = '\0';
	new = safe_strjoin(result, str);
	free(result);
	return (new);
}

char	*append_str(char *result, char *str)
{
	char	*new;

	if (!str)
		return (result);
	new = safe_strjoin(result, str);
	free(result);
	return (new);
}

char	*strip_quotes(char *word)
{
	char			*result;
	t_quote_state	state;
	size_t			i;

	result = safe_strdup("");
	state = Q_NONE;
	i = 0;
	while (word[i])
	{
		if (is_quote_delimiter(word[i], state))
			state = update_quote_state(word[i], state);
		else
			result = append_char(result, word[i]);
		i++;
	}
	return (result);
}
