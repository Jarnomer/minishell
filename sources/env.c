/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/01 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static ssize_t	env_find(t_vec *env, const char *name)
{
	char	*entry;
	size_t	name_len;
	size_t	i;

	name_len = ft_strlen(name);
	i = 0;
	while (i < env->len)
	{
		entry = vec_get(env, i);
		if (ft_strncmp(entry, name, name_len) == 0 && entry[name_len] == '=')
			return (i);
		i++;
	}
	return (-1);
}

static char	*create_entry(const char *name, const char *value)
{
	char	*temp;
	char	*entry;

	temp = safe_strjoin(name, "=");
	entry = safe_strjoin(temp, value);
	free(temp);
	return (entry);
}

void	env_set(t_shell *shell, const char *name, const char *value)
{
	ssize_t	idx;
	char	*entry;

	idx = env_find(&shell->env, name);
	if (idx >= 0)
	{
		free(shell->env.data[idx]);
		shell->env.data[idx] = create_entry(name, value);
		return ;
	}
	entry = create_entry(name, value);
	vec_push(&shell->env, entry);
}

void	env_unset(t_shell *shell, const char *name)
{
	ssize_t	idx;
	size_t	i;

	idx = env_find(&shell->env, name);
	if (idx < 0)
		return ;
	free(shell->env.data[idx]);
	i = idx;
	while (i < shell->env.len - 1)
	{
		shell->env.data[i] = shell->env.data[i + 1];
		i++;
	}
	shell->env.len--;
}

char	*env_get(t_vec *env, const char *name)
{
	char	*entry;
	size_t	name_len;
	size_t	i;

	if (!env || !name)
		return (NULL);
	name_len = ft_strlen(name);
	i = 0;
	while (i < env->len)
	{
		entry = vec_get(env, i);
		if (ft_strncmp(entry, name, name_len) == 0 && entry[name_len] == '=')
			return (entry + name_len + 1);
		i++;
	}
	return (NULL);
}
