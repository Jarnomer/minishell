/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_wildc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/06 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <expand.h>

static void	process_wildcard_arg(t_vec *new_args, char *arg)
{
	t_vec	matches;

	matches = get_matching_files(arg);
	if (matches.len > 0)
		vec_append(new_args, &matches);
	else
		vec_push(new_args, strip_quotes(arg));
	vec_free(&matches, NULL);
	free(arg);
}

static t_quote_state	update_quote(char c, t_quote_state state)
{
	if (c == '\'' && state != Q_DOUBLE)
	{
		if (state == Q_SINGLE)
			return (Q_NONE);
		return (Q_SINGLE);
	}
	if (c == '"' && state != Q_SINGLE)
	{
		if (state == Q_DOUBLE)
			return (Q_NONE);
		return (Q_DOUBLE);
	}
	return (state);
}

static bool	has_unquoted_wildcard(const char *str)
{
	t_quote_state	state;

	state = Q_NONE;
	while (*str)
	{
		if (*str == '\'' || *str == '"')
			state = update_quote(*str, state);
		else if (*str == '*' && state == Q_NONE)
			return (true);
		str++;
	}
	return (false);
}

void	expand_wildcards(t_vec *args)
{
	t_vec	new_args;
	char	*arg;
	size_t	i;

	new_args = vec_new(0);
	i = 0;
	while (i < args->len)
	{
		arg = vec_get(args, i);
		if (has_unquoted_wildcard(arg))
			process_wildcard_arg(&new_args, arg);
		else
		{
			vec_push(&new_args, strip_quotes(arg));
			free(arg);
		}
		i++;
	}
	free(args->data);
	*args = new_args;
}
