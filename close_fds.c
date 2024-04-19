/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_fds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 17:39:53 by jmertane          #+#    #+#             */
/*   Updated: 2024/04/19 15:54:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	reset_shell_fds(t_shell *ms)
{
	ms->pipefd[RD_END] = -1;
	ms->pipefd[WR_END] = -1;
	ms->tempfd = -1;
}

static void	close_shell_fds(t_shell *ms)
{
	if (ms->pipefd[RD_END] != -1)
		close(ms->pipefd[RD_END]);
	if (ms->pipefd[WR_END] != -1)
		close(ms->pipefd[WR_END]);
	if (ms->tempfd != -1)
		close(ms->tempfd);
	reset_shell_fds(ms);
}

static void	close_mod_fds(t_module *mod)
{
	while (mod)
	{
		if (mod->infd != -1)
			close(mod->infd);
		if (mod->outfd != -1)
			close(mod->outfd);
		mod = mod->next;
	}
}

void	close_fds(t_shell *ms)
{
	if (!ms)
		return ;
	if (ms->mods != NULL)
		close_mod_fds(ms->mods);
	close_shell_fds(ms);
}
