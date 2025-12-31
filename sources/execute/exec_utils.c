/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jankku <jankku@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 00:00:00 by jankku            #+#    #+#             */
/*   Updated: 2025/01/01 00:00:00 by jankku           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <execute.h>

int	open_redir_file(t_redir *redir)
{
	if (redir->type == REDIR_IN)
		return (try_open(redir->target, O_RDONLY, 0));
	if (redir->type == REDIR_OUT)
		return (try_open(redir->target, O_WRONLY | O_CREAT | O_TRUNC, 0644));
	if (redir->type == REDIR_APPEND)
		return (try_open(redir->target, O_WRONLY | O_CREAT | O_APPEND, 0644));
	return (-1);
}

static void	close_redirs_heredocs(t_vec *redirs)
{
	t_redir	*redir;
	size_t	i;

	i = 0;
	while (i < redirs->len)
	{
		redir = vec_get(redirs, i);
		if (redir->type == REDIR_HEREDOC && redir->fd >= 0)
			safe_close(redir->fd);
		i++;
	}
}

void	close_heredocs(t_ast *ast)
{
	if (!ast)
		return ;
	if (ast->type == AST_CMD && ast->cmd)
		close_redirs_heredocs(&ast->cmd->redirs);
	else if (ast->type == AST_SUBSHELL)
		close_redirs_heredocs(&ast->redirs);
	close_heredocs(ast->left);
	close_heredocs(ast->right);
}

char	*append_heredoc(char *content, char *line)
{
	char	*temp;

	temp = safe_strjoin(content, line);
	free(content);
	content = safe_strjoin(temp, "\n");
	free(temp);
	free(line);
	return (content);
}

/*
** Print erro message, cleanup context, set exit status
** Returns NULL for return chaining
*/
void	*exec_error_tok(t_exec *ctx, char *tok)
{
	print_error_token(tok);
	exec_cleanup(ctx);
	ctx->shell->exit_status = EC_SYNTAX;
	return (NULL);
}
