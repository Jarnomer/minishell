/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 13:11:26 by jmertane          #+#    #+#             */
/*   Updated: 2024/05/04 17:15:56 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	update_exitcode(int wstat)
{
	// printf("debug printf from update_exitcode\n");
	if (WIFSIGNALED(wstat) != SUCCESS)
		return (ERR_SIG + WTERMSIG(wstat));
	return (WEXITSTATUS(wstat));
}

void	wait_children(t_shell *ms)
{
	int	wstat;
	int	i;

	i = 0;
	if ((ms->forks == 1 && is_builtin2(ms->mods)) || g_signal == 2)
		return ;
	while (i <= ms->index)
	{
		waitpid(ms->pids[i], &wstat, 0);
		ms->excode = update_exitcode(wstat);
		i++;
	}
}
