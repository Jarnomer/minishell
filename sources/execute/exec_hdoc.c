/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_hdoc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/01 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <execute.h>

static void	heredoc_child(t_redir *redir, t_shell *shell, int write_fd)
{
	char	*content;
	char	*line;
	char	*expanded;

	content = safe_strdup("");
	while (1)
	{
		line = readline("> ");
		if (!line || ft_strcmp(line, redir->target) == 0)
		{
			free(line);
			break ;
		}
		if (!redir->quoted)
		{
			expanded = expand_word(line, shell);
			free(line);
			line = expanded;
		}
		content = append_heredoc(content, line);
	}
	ft_putstr_fd(content, write_fd);
	free(content);
	exit(EC_SUCCESS);
}

static int	wait_heredoc(pid_t pid, int read_fd, t_shell *shell)
{
	int	status;

	setup_signals_ignore();
	waitpid(pid, &status, 0);
	setup_signals_interactive();
	if (WIFSIGNALED(status))
	{
		safe_close(read_fd);
		shell->exit_status = SIG_EXITCODE;
		ft_putchar_fd('\n', 1);
		return (-1);
	}
	return (read_fd);
}

static int	setup_one_heredoc(t_redir *redir, t_shell *shell)
{
	int		pipefd[2];
	pid_t	pid;

	if (try_pipe(pipefd) == -1)
		return (-1);
	pid = try_fork(pipefd, 2);
	if (pid == -1)
		return (-1);
	if (pid == 0)
	{
		safe_close(pipefd[0]);
		setup_signals_child();
		heredoc_child(redir, shell, pipefd[1]);
	}
	safe_close(pipefd[1]);
	redir->fd = wait_heredoc(pid, pipefd[0], shell);
	if (redir->fd == -1)
		return (-1);
	return (0);
}

static int	collect_redirs_heredocs(t_vec *redirs, t_shell *shell)
{
	t_redir	*redir;
	size_t	i;

	i = 0;
	while (i < redirs->len)
	{
		redir = vec_get(redirs, i);
		if (redir->type == REDIR_HEREDOC)
		{
			if (setup_one_heredoc(redir, shell) == -1)
				return (-1);
		}
		i++;
	}
	return (0);
}

int	collect_heredocs(t_ast *ast, t_shell *shell)
{
	if (!ast)
		return (0);
	if (ast->type == AST_CMD && ast->cmd)
	{
		if (collect_redirs_heredocs(&ast->cmd->redirs, shell) == -1)
			return (-1);
	}
	if (ast->type == AST_SUBSHELL)
	{
		if (collect_redirs_heredocs(&ast->redirs, shell) == -1)
			return (-1);
	}
	if (collect_heredocs(ast->left, shell) == -1)
		return (-1);
	if (collect_heredocs(ast->right, shell) == -1)
		return (-1);
	return (0);
}
