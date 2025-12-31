/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jankku <jankku@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 00:00:00 by jankku            #+#    #+#             */
/*   Updated: 2025/01/01 00:00:00 by jankku           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <execute.h>
#include <sig.h>

static void	exec_pipe_left(t_ast *ast, t_shell *shell, int pipefd[2])
{
	int	status;

	setup_signals_child();
	safe_close(pipefd[0]);
	if (try_dup2(pipefd[1], STDOUT_FILENO) == -1)
		exit(EC_FAILURE);
	safe_close(pipefd[1]);
	status = exec_ast(ast->left, shell);
	exit(status);
}

static void	exec_pipe_right(t_ast *ast, t_shell *shell, int pipefd[2])
{
	int	status;

	setup_signals_child();
	safe_close(pipefd[1]);
	if (try_dup2(pipefd[0], STDIN_FILENO) == -1)
		exit(EC_FAILURE);
	safe_close(pipefd[0]);
	status = exec_ast(ast->right, shell);
	exit(status);
}

static int	wait_children(pid_t left_pid, pid_t right_pid)
{
	int	status;

	setup_signals_ignore();
	waitpid(left_pid, NULL, 0);
	waitpid(right_pid, &status, 0);
	setup_signals_interactive();
	return (get_exit_status(status));
}

int	exec_pipe(t_ast *ast, t_shell *shell)
{
	int		pipefd[2];
	pid_t	left_pid;
	pid_t	right_pid;

	if (try_pipe(pipefd) == -1)
		return (EC_FAILURE);
	left_pid = try_fork(pipefd, 2);
	if (left_pid == -1)
		return (EC_FAILURE);
	if (left_pid == 0)
		exec_pipe_left(ast, shell, pipefd);
	right_pid = try_fork(pipefd, 2);
	if (right_pid == -1)
	{
		waitpid(left_pid, NULL, 0);
		return (EC_FAILURE);
	}
	if (right_pid == 0)
		exec_pipe_right(ast, shell, pipefd);
	close_pipe(pipefd);
	return (wait_children(left_pid, right_pid));
}
