/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirect.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 19:14:02 by jmertane          #+#    #+#             */
/*   Updated: 2024/05/05 15:53:33 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	redirect_outfd(t_module *mod, t_shell *ms)
{
	if (!mod->outfiles && ms->forks == 1)
		return ;
	else if (!mod->outfiles && ms->index != ms->forks - 1
		&& dup2(ms->pipefd[WR_END], STDOUT) == FAILURE)
		error_exit(ERR_FILE, NULL, NULL, ms);
	else if (mod->outfiles != NULL
		&& dup2(mod->outfd, STDOUT) == FAILURE)
		error_exit(ERR_FILE, NULL, NULL, ms);
}

static void	redirect_infd(t_module *mod, t_shell *ms)
{
	if (!mod->infiles && ms->forks == 1)
		return ;
	else if (!mod->infiles && ms->index != 0
		&& dup2(ms->tempfd, STDIN) == FAILURE)
		error_exit(ERR_FILE, NULL, NULL, ms);
	else if (mod->infiles != NULL
		&& dup2(mod->infd, STDIN) == FAILURE)
		error_exit(ERR_FILE, NULL, NULL, ms);
}

void	redirect_fds(t_module *mod, t_shell *ms)
{
	redirect_infd(mod, ms);
	redirect_outfd(mod, ms);
}
