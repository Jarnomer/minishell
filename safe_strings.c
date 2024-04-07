/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_strings.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 18:26:00 by jmertane          #+#    #+#             */
/*   Updated: 2024/04/07 11:53:28 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	safe_strtrim(char **src, char *set, t_shell *ms)
{
	char	*s;

	if (!src || !*src || !set)
		return ;
	s = ft_strtrim(*src, set);
	if (!s)
		fail_malloc(ms);
	if (src != NULL)
		free(*src);
	*src = s;
}

void	safe_strjoin(char **dst, char *s1, char *s2, t_shell *ms)
{
	char	*s;

	if (!dst || !s1 || !s2)
		return ;
	s = ft_strjoin(s1, s2);
	if (!s)
		fail_malloc(ms);
	if (dst != NULL)
		free(*dst);
	*dst = s;
}

void	safe_strdup(char **dst, char *src, t_shell *ms)
{
	char	*s;

	if (!dst || !src)
		return ;
	s = ft_strdup(src);
	if (!s)
		fail_malloc(ms);
	*dst = s;
}

void	safe_substr(char **dst, char *stt, char *end, t_shell *ms)
{
	char	*s;

	if (!dst)
		return ;
	s = ft_substr(stt, 0, end - stt);
	if (!s)
		fail_malloc(ms);
	if (dst != NULL)
		free(*dst);
	*dst = s;
}
