/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 18:29:11 by jmertane          #+#    #+#             */
/*   Updated: 2024/04/04 18:30:38 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_shell(t_shell *ms)
{
	extern char	**environ;

	ft_bzero(ms, sizeof(*ms));
	ms->envp = environ;
	safe_strdup(&ms->prompt, "minishell~>", ms);
	ms->pipe[RD_END] = -1;
	ms->pipe[WR_END] = -1;
	ms->excode = SUCCESS;
}
