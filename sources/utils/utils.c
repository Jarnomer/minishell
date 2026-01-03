/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/01 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>

void	free_str(void *str)
{
	free(str);
}

bool	is_metachar(char c)
{
	return (c && ft_strchr(METACHAR, c));
}

bool	is_quote(char c)
{
	return (c == '\'' || c == '"');
}

bool	has_quotes(const char *value)
{
	if (!value)
		return (false);
	while (*value)
	{
		if (is_quote(*value))
			return (true);
		value++;
	}
	return (false);
}

char	**vec_to_arr(t_vec *env)
{
	char	**arr;
	size_t	i;

	arr = safe_calloc(sizeof(char *) * (env->len + 1));
	i = 0;
	while (i < env->len)
	{
		arr[i] = env->data[i];
		i++;
	}
	return (arr);
}
