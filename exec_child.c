/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 13:10:57 by jmertane          #+#    #+#             */
/*   Updated: 2024/04/13 15:15:59 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	child_process(t_module *mod, t_shell *ms)
{
	redirect_fds(mod, ms);
	close_fds(ms);
	execute_command(mod, ms);
}

static void	parent_process(t_shell *ms)
{
	close(ms->pipefd[WR_END]);
	if (ms->tempfd != -1)
		close(ms->tempfd);
	ms->tempfd = dup(ms->pipefd[RD_END]);
	close(ms->pipefd[RD_END]);
}

static void	fork_process(t_module *mod, t_shell *ms, int process_limit)
{
	if (ms->idx <= process_limit - 1
		&& pipe(ms->pipefd) == FAILURE)
		error_fatal(errno, MSG_PIPE, ms);
	ms->pids[ms->idx] = fork();
	if (ms->pids[ms->idx] == FAILURE)
		error_fatal(errno, MSG_FORK, ms);
	else if (ms->pids[ms->idx] != 0)
		parent_process(ms);
	else if (ms->pids[ms->idx] == 0)
		child_process(mod, ms);
}

void	execute_children(t_shell *ms)
{
	t_module	*mod;
	int			process_limit;

	mod = ms->mods;
	process_limit = ms->cmds - 1;
	while (ms->idx <= process_limit)
	{
		fork_process(mod, ms, process_limit);
		mod = mod->next;
		ms->idx++;
	}
}
