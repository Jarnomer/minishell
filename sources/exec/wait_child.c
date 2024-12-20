/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 13:11:26 by jmertane          #+#    #+#             */
/*   Updated: 2024/05/06 17:57:41 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	update_exitcode(int wstat)
{
	if (WIFSIGNALED(wstat) != 0)
		return (ERR_SIG + WTERMSIG(wstat));
	return (WEXITSTATUS(wstat));
}

void	wait_children(t_shell *ms)
{
	int	wstat;
	int	i;

	i = 0;
	if ((ms->forks == 1 && is_builtin2(ms->mods))
		|| g_signal == SIGINT)
		return ;
	while (i <= ms->index)
	{
		waitpid(ms->pids[i], &wstat, 0);
		ms->exitcode = update_exitcode(wstat);
		i++;
	}
}
