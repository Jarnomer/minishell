/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 13:10:57 by jmertane          #+#    #+#             */
/*   Updated: 2024/05/16 20:50:56 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static bool	executable_exists(t_parser *cmd)
{
	if (!cmd)
		return (false);
	else if (!*cmd->content && cmd->meta == '$' && parser_length(cmd) == 1)
		return (false);
	else if ((ft_strlen(cmd->content) == 1 && *cmd->content == ':'))
		return (false);
	return (true);
}

static void	child_process(t_module *mod, t_shell *ms)
{
	t_parser	*cmd;

	if ((mod->infiles || mod->outfiles)
		&& parse_files(mod, ms) == FAILURE)
		error_exit(ERR_FILE, NULL, NULL, ms);
	redirect_fds(mod, ms);
	close_fds(ms);
	cmd = mod->command;
	if (!executable_exists(cmd))
		error_exit(NOERROR, NULL, NULL, ms);
	else if (is_builtin(mod))
		execute_builtin(ms, mod);
	else
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

static void	fork_process(t_module *mod, t_shell *ms)
{
	ms->pids[ms->index] = fork();
	if (ms->pids[ms->index] == FAILURE)
		error_fatal(errno, MSG_FORK, ms);
	else if (ms->pids[ms->index] != 0)
		parent_process(ms);
	else if (ms->pids[ms->index] == 0)
		child_process(mod, ms);
}

void	execute_children(t_shell *ms)
{
	t_module	*mod;
	int			fork_limit;
	int			pipe_limit;

	mod = ms->mods;
	open_heredocs(mod, ms);
	if (g_signal == 2)
		return ;
	fork_limit = ms->forks - 1;
	pipe_limit = fork_limit - 1;
	while (ms->index <= fork_limit)
	{
		if (ms->index <= pipe_limit
			&& pipe(ms->pipefd) == FAILURE)
			error_fatal(errno, MSG_PIPE, ms);
		if (ms->forks == 1 && is_builtin2(mod))
			execute_builtin(ms, mod);
		else
			fork_process(mod, ms);
		mod = mod->next;
		ms->index++;
	}
}
