/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 13:11:26 by jmertane          #+#    #+#             */
/*   Updated: 2024/04/30 20:16:17 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	receive_signal(int wstat, t_shell *ms)
{
	if (WTERMSIG(wstat) == SIGPIPE)
		error_logger(MSG_SIGPIPE, "", "", ms);
	else if (WTERMSIG(wstat) == SIGCHLD)
		error_logger(MSG_SIGCHLD, "", "", ms);
	else if (WTERMSIG(wstat) == SIGSEGV)
		error_logger(MSG_SIGSEGV, "", "", ms);
	else if (WTERMSIG(wstat) == SIGBUS)
		error_logger(MSG_SIGBUS, "", "", ms);
	else if (WTERMSIG(wstat) == SIGKILL)
		error_logger(MSG_SIGKILL, "", "", ms);
	else if (WTERMSIG(wstat) == SIGABRT)
		error_logger(MSG_SIGABRT, "", "", ms);
	else if (WTERMSIG(wstat) == SIGTERM)
		error_logger(MSG_SIGTERM, "", "", ms);
	else if (WTERMSIG(wstat) != SIGINT
		|| WTERMSIG(wstat) != SIGQUIT)
		error_logger(MSG_SIGOTHR, "", "", ms);
	return (ERR_SIG + WTERMSIG(wstat));
}

static int	update_exitcode(int wstat, t_shell *ms)
{
	if (WIFSIGNALED(wstat) != SUCCESS)
		return (receive_signal(wstat, ms));
	return (WEXITSTATUS(wstat));
}

void	wait_children(t_shell *ms)
{
	int	wstat;
	int	i;

	i = 0;
	if (ms->forks == 1 && is_builtin2(ms->mods))
		return ;
	if (g_sigint == true)
		return ;
	while (i <= ms->index)
	{
		waitpid(ms->pids[i], &wstat, 0);
		ms->excode = update_exitcode(wstat, ms);
		i++;
	}
}
