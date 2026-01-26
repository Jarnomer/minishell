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
	if (ft_strchr(value, '\''))
		return (true);
	if (ft_strchr(value, '"'))
		return (true);
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

void	free_arr(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}
