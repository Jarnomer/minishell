/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 13:10:57 by jmertane          #+#    #+#             */
/*   Updated: 2024/04/07 12:22:27 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	execute_cmd(t_shell *ms)
{
	// execve or buildin
}

static void	replace_io(int input, int output, t_shell *ms)
{
	if (dup2(input, STDIN_FILENO) == -1
		|| (dup2(output, STDOUT_FILENO) == -1))
		perror("Dup2 error"); // do error handling
}

static void	redirect_fds(t_module *mod, t_shell *ms, int i)
{
	if (!i)
		replace_io(mod->infd, ms->pipefd[WR_END], ms);
	else if (i != ms->cmds)
		replace_io(ms->tempfd, ms->pipefd[WR_END], ms);
	else
		replace_io(ms->tempfd, mod->outfd, ms);
}

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
			perror(MSG_PIPE); // fatal error
		ms->pids[i] = fork();
		if (ms->pids[i] == FAILURE)
			perror(MSG_FORK); // fatal error
		else if (ms->pids[i] != 0)
		{
			// do main process stuff
			prep_next_pipe(ms);
			mod = mod->next;
			i++;
		}
		else if (ms->pids[i]  == 0)
		{
			redirect_fds(mod, ms, i);
			close_fds(ms);
			// do child process stuff

		}
	}
}
