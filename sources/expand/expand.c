/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/01 00:00:00 by jmertane         ###   ########.fr       */
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
		if (redir->type == REDIR_HEREDOC && redir->quoted)
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

static void	remove_empty_args(t_vec *args)
{
	size_t	i;
	char	*arg;

	i = 0;
	while (i < args->len)
	{
		arg = args->data[i];
		if (arg[0] == '\0')
			vec_remove(args, i, free);
		else
			i++;
	}
}

void	expand_cmd(t_cmd *cmd, t_shell *shell)
{
	if (!cmd)
		return ;
	expand_args(&cmd->args, shell);
	remove_empty_args(&cmd->args);
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
