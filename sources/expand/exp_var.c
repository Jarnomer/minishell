/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/01 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <expand.h>

static bool	is_valid_var_char(char c, bool first)
{
	if (first)
		return (ft_isalpha(c) || c == '_');
	return (ft_isalnum(c) || c == '_');
}

char	*get_var_name(const char *str, size_t *len)
{
	size_t	i;

	*len = 0;
	if (!str || !*str)
		return (NULL);
	if (str[0] == '?')
	{
		*len = 1;
		return (safe_strdup("?"));
	}
	if (ft_isdigit(str[0]))
	{
		*len = 1;
		return (safe_substr(str, 0, 1));
	}
	if (!is_valid_var_char(str[0], true))
		return (NULL);
	i = 0;
	while (str[i] && is_valid_var_char(str[i], i == 0))
		i++;
	if (i == 0)
		return (NULL);
	*len = i;
	return (safe_substr(str, 0, i));
}

char	*expand_var(char *name, t_shell *shell)
{
	char	*value;

	if (!name)
		return (NULL);
	if (ft_strcmp(name, "?") == 0)
		return (safe_itoa(shell->exit_status));
	value = env_get(&shell->env, name);
	if (value)
		return (safe_strdup(value));
	return (safe_strdup(""));
}
