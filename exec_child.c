/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 13:10:57 by jmertane          #+#    #+#             */
/*   Updated: 2024/04/14 19:01:13 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	child_process(t_module *mod, t_shell *ms)
{
	redirect_fds(mod, ms);
	close_fds(ms);
	if (!mod->command)
		error_exit(NOERROR, NULL, NULL, ms);
	// else if (cant_run_cmd == FAILURE)
	// 	error_exit(ms->excode, NULL, NULL, ms);
	else if (is_builtin(mod->command->content))
		execute_builtin(ms, mod);
	else
		execute_command(mod, ms);
	exit(0);
}

static void	parent_process(t_shell *ms)
{
	close(ms->pipefd[WR_END]);
	if (ms->tempfd != -1)
		close(ms->tempfd);
	ms->tempfd = dup(ms->pipefd[RD_END]);
	close(ms->pipefd[RD_END]);
}

static void	fork_process(t_module *mod, t_shell *ms)
{
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
	int			pipe_limit;

	mod = ms->mods;
	process_limit = ms->cmds - 1;
	pipe_limit = process_limit - 1;
	while (ms->idx <= process_limit)
	{
		if (ms->idx <= pipe_limit
			&& pipe(ms->pipefd) == FAILURE)
			error_fatal(errno, MSG_PIPE, ms);
		if (ms->cmds == 1 && is_builtin(mod->command->content))
			execute_builtin(ms, mod);
		else
			fork_process(mod, ms);
		mod = mod->next;
		ms->idx++;
	}
}
