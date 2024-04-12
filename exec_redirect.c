/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirect.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 19:14:02 by jmertane          #+#    #+#             */
/*   Updated: 2024/04/09 19:24:04 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	redirect_outfd(t_module *mod, t_shell *ms)
{
	if (!mod->outfiles && ms->cmds == 1)
		return ;
	else if (!mod->outfiles && ms->idx != ms->cmds - 1
		&& dup2(ms->pipefd[WR_END], STDOUT) == FAILURE)
		error_exit(ERR_FILE, NULL, NULL, ms);
	else if (mod->infiles != NULL
		&& dup2(open_infile(mod, ms), STDOUT) == FAILURE)
		error_exit(ERR_FILE, NULL, NULL, ms);
}

static void	redirect_infd(t_module *mod, t_shell *ms)
{
	if (!mod->infiles && ms->cmds == 1)
		return ;
	else if (!mod->infiles && ms->idx != 0
		&& dup2(ms->tempfd, STDIN) == FAILURE)
		error_exit(ERR_FILE, NULL, NULL, ms);
	else if (mod->infiles != NULL
		&& dup2(open_infile(mod, ms), STDIN) == FAILURE)
		error_exit(ERR_FILE, NULL, NULL, ms);
}

void	redirect_fds(t_module *mod, t_shell *ms)
{
	redirect_infd(mod, ms);
	redirect_outfd(mod, ms);
}
