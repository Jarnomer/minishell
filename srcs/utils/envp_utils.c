/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 13:09:20 by vkinaret          #+#    #+#             */
/*   Updated: 2024/05/16 19:06:55 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static	void	error_occured(char ***arr, t_shell *ms)
{
	free_double(arr);
	error_fatal(ENOMEM, MSG_MEM, ms);
}

char	*envp_exists(char *name, t_shell *ms)
{
	char	*temp;
	int		len;
	int		i;

	i = 0;
	temp = safe_trash(ft_strjoin(name, "="), ALLOCATED, ms);
	len = ft_strlen(temp);
	while (ms->envp[i] && !ft_strnstr(ms->envp[i], temp, len))
		i++;
	if (ms->envp[i] != NULL)
		return (ms->envp[i] + len);
	return (NULL);
}

void	envp_update(t_shell *ms, char *content)
{
	int		i;
	int		size;

	i = 0;
	size = 0;
	while (content[size] != '=')
		size++;
	while (i < ms->envp_size)
	{
		if (!ft_strncmp(ms->envp[i], content, size))
			break ;
		i++;
	}
	safe_strjoin(&ms->envp[i], "", content, ms);
}

void	envp_add(t_shell *ms, char *content)
{
	char	**new_envp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	ms->envp_size += 1;
	new_envp = safe_calloc((ms->envp_size + 1) * sizeof(char *), ms);
	while (i < ms->envp_size)
	{
		if (!ft_strncmp(ms->envp[j], "_=", 2))
		{
			new_envp[i] = ft_strdup(content);
			if (!new_envp[i])
				error_occured(&new_envp, ms);
			i++;
		}
		new_envp[i] = ft_strdup(ms->envp[j]);
		if (!new_envp[i])
			error_occured(&new_envp, ms);
		i++;
		j++;
	}
	free_double(&ms->envp);
	ms->envp = new_envp;
}

void	envp_remove(t_shell *ms, char *content)
{
	int		i;
	int		j;
	int		len;
	char	**new_envp;

	i = 0;
	j = 0;
	len = ft_strlen(content);
	ms->envp_size -= 1;
	new_envp = safe_calloc((ms->envp_size + 1) * sizeof(char *), ms);
	while (i < ms->envp_size)
	{
		if (!ft_strncmp(ms->envp[j], content, len)
			&& ((ms->envp[j][len]) == '=' || (ms->envp[j][len]) == '\0'))
			j++;
		new_envp[i] = ft_strdup(ms->envp[j]);
		if (!new_envp[i])
			error_occured(&new_envp, ms);
		i++;
		j++;
	}
	free_double(&ms->envp);
	ms->envp = new_envp;
}
