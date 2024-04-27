/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_envps.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 19:03:40 by jmertane          #+#    #+#             */
/*   Updated: 2024/04/27 15:20:05 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*expand_envp(char *buffer, char *temp, t_shell *ms)
{
	char	*envp;
	int		len;

	envp = temp;
	temp = find_breakpoint(temp);
	envp = safe_trash(ft_substr(envp, 0, temp - envp), ALLOCATED, ms);
	envp = envp_exists(envp, ms);
	if (!envp)
		return (temp);
	len = ft_strlen(buffer) + ft_strlen(envp) + 1;
	ft_strlcat(buffer, envp, len);
	return (temp);
}

static char	*expand_excode(char *buffer, char *temp, t_shell *ms)
{
	char	*excode;
	int		len;

	excode = safe_trash(ft_itoa(ms->excode), ALLOCATED, ms);
	len = ft_strlen(buffer) + ft_strlen(excode) + 1;
	ft_strlcat(buffer, excode, len);
	return (temp + 1);
}

static char	*parse_dollar(char *buffer, char *temp, t_shell *ms)
{
	if (!*temp || ft_isredirect(*temp) || ft_ismeta(*temp))
	{
		ft_strlcat(buffer, temp - 1, ft_strlen(buffer) + 3);
		if (*temp)
			temp++;
		return (temp);
	}
	else if (*temp == QUESTIONMARK)
		return (expand_excode(buffer, temp, ms));
	else
		return (expand_envp(buffer, temp, ms));
}

void	parse_envps(t_parser *new, t_shell *ms)
{
	char	buffer[1000];
	char	*envp;
	char	*temp;
	int		len;

	temp = new->content;
	if (!temp || !*temp || ft_strlen(temp) == 1)
		return ;
	ft_bzero(buffer, 1000);
	while (*temp)
	{
		envp = temp;
		while (*temp && *temp != DOLLAR)
			temp++;
		len = ft_strlen(buffer) + (temp - envp + 1);
		ft_strlcat(buffer, envp, len);
		if (!*temp)
			break ;
		else
			temp = parse_dollar(buffer, ++temp, ms);
	}
	free_single(&new->content);
	safe_strdup(&new->content, buffer, ms);
}
