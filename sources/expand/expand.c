/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jankku <jankku@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 00:00:00 by jankku            #+#    #+#             */
/*   Updated: 2025/01/01 00:00:00 by jankku           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <expand.h>

static void	expand_args(t_vec *args, t_shell *shell)
{
	char	*old;
	char	*new;
	size_t	i;

	i = 0;
	while (i < args->len)
	{
		old = args->data[i];
		new = expand_word(old, shell);
		free(old);
		args->data[i] = new;
		i++;
	}
}

static bool	skip_redir_expand(t_redir *redir)
{
	return (redir->type == REDIR_HEREDOC && redir->quoted);
}

static void	expand_redirs(t_vec *redirs, t_shell *shell)
{
	t_redir	*redir;
	char	*old;
	char	*new;
	size_t	i;

	i = 0;
	while (i < redirs->len)
	{
		redir = redirs->data[i];
		if (skip_redir_expand(redir))
		{
			i++;
			continue ;
		}
		old = redir->target;
		new = expand_word(old, shell);
		free(old);
		redir->target = new;
		i++;
	}
}

void	expand_cmd(t_cmd *cmd, t_shell *shell)
{
	if (!cmd)
		return ;
	expand_args(&cmd->args, shell);
	expand_wildcards(&cmd->args);
	expand_redirs(&cmd->redirs, shell);
}

void	expand_ast(t_ast *ast, t_shell *shell)
{
	if (!ast)
		return ;
	if (ast->type == AST_CMD)
		expand_cmd(ast->cmd, shell);
	if (ast->type == AST_SUBSHELL && ast->redirs.len > 0)
		expand_redirs(&ast->redirs, shell);
	expand_ast(ast->left, shell);
	expand_ast(ast->right, shell);
}
