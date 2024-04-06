/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 13:10:57 by jmertane          #+#    #+#             */
/*   Updated: 2024/04/06 15:11:07 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	prep_next_pipe(t_shell *ms)
{
	close(ms->pipefd[WR_END]);
	if (ms->tempfd != -1)
		close(ms->tempfd);
	ms->tempfd = dup(ms->pipefd[RD_END]);
	close(ms->pipefd[RD_END]);
}

void	exec_children(t_shell *ms)
{
	t_module	*mod;
	int			i;

	i = 0;
	mod = ms->mods;
	while (i <= ms->cmds)
	{
		if (i != ms->cmds && pipe(ms->pipefd) == FAILURE)
			perror(MSG_PIPE);
		ms->pids[i] = fork();
		if (ms->pids[i] == FAILURE)
			perror(MSG_FORK);
		else if (ms->pids[i] != 0)
		{
			// do main process stuff
			prep_next_pipe(ms);
			mod = mod->next;
			i++;
		}
		else if (ms->pids[i]  == 0)
		{
			// do child process stuff
		}
	}
}
