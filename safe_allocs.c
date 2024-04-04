/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_allocs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 18:25:54 by jmertane          #+#    #+#             */
/*   Updated: 2024/04/04 18:25:56 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fail_malloc(t_shell *ms)
{
	perror(MSG_MEM);
	free_runtime(ms, FAILURE);
	exit(ENOMEM);
}

void	*safe_calloc(size_t n, t_shell *ms)
{
	void	*p;

	p = ft_calloc(1, n);
	if (!p)
		fail_malloc(ms);
	return (p);
}
