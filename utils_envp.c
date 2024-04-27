/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_envp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 13:09:20 by vkinaret          #+#    #+#             */
/*   Updated: 2024/04/17 18:58:25 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*envp_exists(char *name, t_shell *ms)
{
	char	*temp;
	int		len;
	int		i;

	i = 0;
	temp = NULL;
	safe_strjoin(&temp, name, "=", ms);
	len = ft_strlen(temp);
	while (ms->envp[i] && !ft_strnstr(ms->envp[i], temp, len))
		i++;
	free_single(&temp);
	if (ms->envp[i] != NULL)
		return (ms->envp[i] + len);
	return (NULL);
}

void	envp_update(t_shell *ms, char *content)
{
	int		i;
	int		size;
	char	*temp;

	i = 0;
	size = 0;
	while (content[size] != '=')
		size++;
	while (i < ms->envp_size)
	{
		if (ft_strncmp(ms->envp[i], content, size) == 0)
			break ;
		i++;
	}
	temp = ms->envp[i];
	ms->envp[i] = ft_strdup(content);
	free(temp);
}

void	envp_add(t_shell *ms, char *content)
{
	int 	i;
	int 	j;
	char	**new_envp;

	i = 0;
	j = 0;
	ms->envp_size += 1;
	new_envp = safe_calloc((ms->envp_size + 1) * sizeof(char *), ms);
	while (i < ms->envp_size)
	{
		if (ft_strncmp(ms->envp[j], "_=", 2) == 0)
		{
			new_envp[i] = ft_strdup(content);
			i++;
		}
		new_envp[i] = ft_strdup(ms->envp[j]);
		i++;
		j++;
	}
	new_envp[i] = NULL;
	free_double(&ms->envp);
	ms->envp = new_envp;
}

void	envp_remove(t_shell *ms, char *content)
{
	int		i;
	int		j;
	char	**new_envp;

	i = 0;
	j = 0;
	ms->envp_size -= 1;
	new_envp = safe_calloc((ms->envp_size + 1) * sizeof(char *), ms);
	while (i < ms->envp_size)
	{
		if (ft_strncmp(ms->envp[j], content, ft_strlen(content)) == 0)
			j++;
		new_envp[i] = ft_strdup(ms->envp[j]);
		i++;
		j++;
	}
	new_envp[i] = NULL;
	free_double(&ms->envp);
	ms->envp = new_envp;
}
