/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_subs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/01 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <execute.h>

static int	wait_subshell(pid_t pid)
{
	int	status;

	setup_signals_ignore();
	waitpid(pid, &status, 0);
	setup_signals_interactive();
	return (get_exit_status(status));
}

int	exec_subshell(t_ast *ast, t_shell *shell)
{
	pid_t	pid;
	int		status;

	pid = try_fork(NULL, 0);
	if (pid == -1)
		return (EC_FAILURE);
	if (pid == 0)
	{
		setup_signals_child();
		if (ast->redirs.len > 0 && apply_redirs(&ast->redirs) == -1)
			exit(EC_FAILURE);
		status = exec_ast(ast->left, shell);
		exit(status);
	}
	return (wait_subshell(pid));
}
