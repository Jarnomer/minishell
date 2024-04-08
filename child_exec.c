/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 13:10:57 by jmertane          #+#    #+#             */
/*   Updated: 2024/04/07 20:28:40 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>

static int	argument_count(t_parser	*file)
{
	int	len;

	len = 0;
	while (file)
	{
		file = file->next;
		len++;
	}
	return (len);
}

static char	**build_command(t_parser *command, t_shell *ms)
{
	char	**cmd;
	int		i;

	cmd = safe_calloc((argument_count(command) + 1) * sizeof(char *), ms);
	i = 0;
	while (cmd[i])
	{
		cmd[i] = command->content;
		command = command->next;
		i++;
	}
	return (cmd);
}

static void	execute_cmd(t_module *mod, t_shell *ms)
{
	char	**cmd;
	char	*exec;

	// check if buildin
	exec = mod->command->content;
	exec = executable_path(exec, ms);
	cmd = build_command(mod->command, ms);
	execve(exec, cmd, ms->envp);
}

static void	replace_io(int input, int output, t_shell *ms)
{
	if (dup2(input, STDIN_FILENO) == FAILURE
		|| (dup2(output, STDOUT_FILENO) == FAILURE))
		error_exit(ERR_FILE, NULL, ms);
}

static void	redirect_fds(t_module *mod, t_shell *ms, int i)
{
	int	infd;
	int	outfd;
	if (!i && mod->infiles != NULL)
		replace_io(open_infile(mod, ms), ms->pipefd[WR_END], ms);
	else if (i != ms->cmds)
		replace_io(ms->tempfd, ms->pipefd[WR_END], ms);
	else if (mod->outfiles != NULL)
		replace_io(ms->tempfd, open_outfile(mod), ms);
	if (infd != -1)
		close(infd);
	if (outfd != -1)
		close(outfd);
}

static void	prep_next_pipe(t_shell *ms)
{
	close(ms->pipefd[WR_END]);
	if (ms->tempfd != -1)
		close(ms->tempfd);
	ms->tempfd = dup(ms->pipefd[RD_END]);
	close(ms->pipefd[RD_END]);
}

void	execute_children(t_shell *ms)
{
	t_module	*mod;
	int			i;

	i = 0;
	while (i <= ms->cmds)
	{
		if (i == 0)
			mod = ms->mods;
		if (i != ms->cmds && pipe(ms->pipefd) == FAILURE)
			perror(MSG_PIPE); // fatal error
		ms->pids[i] = fork();
		if (ms->pids[i] == FAILURE)
			perror(MSG_FORK); // fatal error
		else if (ms->pids[i] != 0)
		{
			prep_next_pipe(ms);
			mod = mod->next;
			i++;
		}
		else if (ms->pids[i] == 0)
		{
			redirect_fds(mod, ms, i);
			close_fds(ms);
			execute_cmd(mod, ms);
		}
	}
}
