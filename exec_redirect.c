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

// static int	verify_outdirect(t_module *mod, t_shell *ms)
// {
// 	if (!mod->outfiles && ms->idx != ms->cmds - 1)
// 		return (ms->pipefd[WR_END]);
// 	else if (mod->outfiles != NULL)
// 		return (open_outfile(mod, ms));
// 	else
// 		return (STDOUT_FILENO);
// }

// static int	verify_indirect(t_module *mod, t_shell *ms)
// {
// 	if (!mod->infiles && ms->idx != 0 && ms->idx != ms->cmds)
// 		return (ms->tempfd);
// 	else if (mod->infiles != NULL)
// 		return (open_infile(mod, ms));
// 	else
// 		return (STDIN_FILENO);
// }

// static void	redirect_fds(t_module *mod, t_shell *ms)
// {
// 	int	infd;
// 	int	outfd;

// 	infd = verify_indirect(mod,ms);
// 	outfd = verify_outdirect(mod, ms);
// 	printf("Child process[%d]: infd is: %d, outfd is: %d\n", ms->idx, infd, outfd);
// 	if (dup2(infd, STDIN_FILENO) == FAILURE)
// 		perror("Dup2 error");
// 		// error_exit(ERR_FILE, ms);
// 	if (dup2(outfd, STDOUT_FILENO) == FAILURE)
// 		perror("Dup2 error");
// 		// error_exit(ERR_FILE, ms);
// 	if (infd != 0 && infd != ms->tempfd && infd != -1)
// 		close(infd);
// 	if (outfd != 1 && outfd != ms->pipefd[WR_END] && outfd != -1)
// 		close(outfd);
// }

// static void	replace_io(int input, int output, t_shell *ms)
// {
// 	if (output == 32745)
// 		exit (9001);
// 	printf("idx[%d] | cmds[%d]\n", ms->idx, ms->cmds);
// 	if (ms->idx != 0)
// 		if (dup2(input, STDIN_FILENO) == -1)
// 			perror("Dup2 error");
// 	// if (ms->idx != ms->cmds - 2)
// 	// 	if (dup2(output, STDOUT_FILENO) == -1)
// 	// 		perror("Dup2 error");
// }

static void	replace_io(int input, int output, t_shell *ms)
{
	if (!ms)
		perror("Dup2 error");
	if (dup2(input, STDIN_FILENO) == -1)
		perror("Dup2 error");
	if (dup2(output, STDOUT_FILENO) == -1)
		perror("Dup2 error");
}

void	redirect_fds(t_module *mod, t_shell *ms)
{
	if (!mod)
		printf("lol");
	if (ms->cmds == 1)
		return ;
	if (ms->idx == 0)
		replace_io(STDIN, ms->pipefd[WR_END], ms);
	else if (ms->idx < ms->cmds - 1)
		replace_io(ms->tempfd, ms->pipefd[WR_END], ms);
	else
		replace_io(ms->tempfd, STDOUT_FILENO, ms);
}
