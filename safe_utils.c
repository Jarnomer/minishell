/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkinaret <vkinaret@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 14:09:56 by vkinaret          #+#    #+#             */
/*   Updated: 2024/04/02 14:09:58 by vkinaret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	safe_fn_error(t_shell *ms)
{
	perror("Out of memory");
	free_struct(ms);
	exit(ENOMEM);
}

void	safe_strtrim(char **src, char *set, t_shell *ms)
{
	char	*s;

	if (!src || !*src || !set)
		return ;
	s = ft_strtrim(*src, set);
	if (!s)
		safe_fn_error(ms);
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
		safe_fn_error(ms);
	free(*dst);
	*dst = s;
}

void	safe_strdup(char **dst, char *src, t_shell *ms)
{
	char	*s;

	if (!dst || !src || !*src)
		return ;
	s = ft_strdup(src);
	if (!s)
		safe_fn_error(ms);
	free(*dst);
	*dst = s;
}

void	safe_substr(char **dst, char *stt, char *end, t_shell *ms)
{
	char	*s;

	if (!dst || stt >= end)
		return ;
	s = ft_substr(stt, 0, end - stt);
	if (!s)
		safe_fn_error(ms);
	free(*dst);
	*dst = s;
}

void	*safe_calloc(size_t n, t_shell *ms)
{
	void	*p;

	p = ft_calloc(1, n);
	if (!p)
		safe_fn_error(ms);
	return (p);
}
