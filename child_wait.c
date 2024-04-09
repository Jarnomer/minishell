/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_wait.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 13:11:26 by jmertane          #+#    #+#             */
/*   Updated: 2024/04/09 13:46:58 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	update_exitcode(int wstat)
{
	return (WEXITSTATUS(wstat));
}

void	wait_children(t_shell *ms)
{
	int	wstat;
	int	i;

	i = 0;
	while (i < ms->cmds)
	{
		waitpid(ms->pids[i++], &wstat, 0);
		ms->excode = update_exitcode(wstat);
	}
}
