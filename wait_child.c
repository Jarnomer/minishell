/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 13:11:26 by jmertane          #+#    #+#             */
/*   Updated: 2024/04/09 19:17:01 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static inline int	update_exitcode(int wstat)
{
	return (WEXITSTATUS(wstat));
}

void	wait_children(t_shell *ms)
{
	int	wstat;
	int	i;

	i = 0;
	if (ms->cmds == 1 && is_builtin(ms->mods->command->content))
		return ;
	while (i < ms->idx)
	{
		waitpid(ms->pids[i], &wstat, 0);
		ms->excode = update_exitcode(wstat);
		i++;
	}
}
