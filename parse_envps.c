/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_envps.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 19:03:40 by jmertane          #+#    #+#             */
/*   Updated: 2024/04/25 20:54:06 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*expand_envp(char *buffer, char *temp, t_shell *ms)
{
	char	*envp;

	if (!*temp || ft_isredirect(*temp) || ft_ismeta(*temp))
	{
		ft_strlcat(buffer, temp, 2);
		return (temp + 1);
	}
	else if (*temp == QUESTIONMARK)
	{
		envp = safe_trash(ft_itoa(ms->excode), ALLOCATED, ms);
		ft_strlcat(buffer, envp, ft_strlen(envp) + 1);
		return (temp + 1);
	}
	else
	{
		envp = temp;
		temp = find_breakpoint(temp);
		envp = safe_trash(ft_substr(envp, 0, temp - envp), ALLOCATED, ms);
		envp = envp_exists(envp, ms);
		if (envp != NULL)
			ft_strlcat(buffer, envp, ft_strlen(envp) + 1);
		return (temp);
	}
}

void	parse_envps(t_parser *new, t_shell *ms)
{
	char	buffer[1000];
	char	*envp;
	char	*temp;

	temp = new->content;
	if (!temp || !*temp || ft_strlen(temp) == 1)
		return ;
	ft_bzero(buffer, 1000);
	while (*temp)
	{
		envp = temp;
		while (*temp && *temp != DOLLAR)
			temp++;
		ft_strlcat(buffer, temp, temp - envp);
		if (!*temp)
			break ;
		else
			temp = expand_envp(buffer, ++temp, ms);
	}
	free_single(&new->content);
	safe_strdup(&new->content, buffer, ms);
}
