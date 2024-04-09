/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 13:10:57 by jmertane          #+#    #+#             */
/*   Updated: 2024/04/09 13:43:21 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**build_command(t_parser *command, t_shell *ms)
{
	char	**cmd;
	int		i;

	cmd = safe_calloc((parser_length(command) + 1) * sizeof(char *), ms);
	i = 0;
	while (command)
	{
		cmd[i++] = command->content;
		command = command->next;
	}
	return (cmd);
}

static void	execute_cmd(t_module *mod, t_shell *ms)
{
	char	**cmd;
	char	*exec;

	exec = mod->command->content;
	exec = executable_path(exec, ms);
	cmd = build_command(mod->command, ms);
	execve(exec, cmd, ms->envp);
}

static int	verify_outdirect(t_module *mod, t_shell *ms)
{
	if (mod->outfiles != NULL)
		return (open_outfile(mod));
	else if (ms->cmds != 0 && ms->idx != ms->cmds)
		return (ms->pipefd[WR_END]);
	else
		return (STDOUT_FILENO);
}

static int	verify_indirect(t_module *mod, t_shell *ms)
{
	if (mod->infiles != NULL)
		return (open_infile(mod, ms));
	else if (ms->cmds != 0)
		return (ms->tempfd);
	else
		return (STDIN_FILENO);
}

static void	redirect_fds(t_module *mod, t_shell *ms)
{
	int	infd;
	int	outfd;

	if (ms->cmds == 1)
		return ;
	infd = verify_indirect(mod,ms);
	outfd = verify_outdirect(mod, ms);
	if (dup2(infd, STDIN_FILENO) == FAILURE)
		perror("Dup2 error");
		// error_exit(ERR_FILE, ms);
	if (dup2(outfd, STDOUT_FILENO) == FAILURE)
		perror("Dup2 error");
		// error_exit(ERR_FILE, ms);
	if (infd != -1)
		close(infd);
	if (outfd != -1)
		close(outfd);
}

static void	prep_next_pipe(t_shell *ms)
{
	if (ms->cmds == 1)
		return ;
	close(ms->pipefd[WR_END]);
	if (ms->tempfd != -1)
		close(ms->tempfd);
	ms->tempfd = dup(ms->pipefd[RD_END]);
	close(ms->pipefd[RD_END]);
}

void	execute_children(t_shell *ms)
{
	t_module	*mod;

	while (ms->idx < ms->cmds)
	{
		if (ms->idx == 0)
			mod = ms->mods;
		if (ms->idx != ms->cmds
			&& pipe(ms->pipefd) == FAILURE)
			error_fatal(errno, MSG_PIPE, ms);
		ms->pids[ms->idx] = fork();
		if (ms->pids[ms->idx] == FAILURE)
			error_fatal(errno, MSG_FORK, ms);
		else if (ms->pids[ms->idx] != 0)
		{
			prep_next_pipe(ms);
			mod = mod->next;
			ms->idx++;
		}
		else if (ms->pids[ms->idx] == 0)
		{
			redirect_fds(mod, ms);
			close_fds(ms);
			execute_cmd(mod, ms);
		}
	}
}
