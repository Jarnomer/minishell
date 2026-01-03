/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/01 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <execute.h>

static int	exec_and(t_ast *ast, t_shell *shell)
{
	int	status;

	status = exec_ast(ast->left, shell);
	if (status == EC_SUCCESS)
		status = exec_ast(ast->right, shell);
	return (status);
}

static int	exec_or(t_ast *ast, t_shell *shell)
{
	int	status;

	status = exec_ast(ast->left, shell);
	if (status == EC_FAILURE)
		status = exec_ast(ast->right, shell);
	return (status);
}

int	exec_ast(t_ast *ast, t_shell *shell)
{
	if (!ast)
		return (EC_SUCCESS);
	if (ast->type == AST_CMD)
		return (exec_simple_cmd(ast->cmd, shell));
	if (ast->type == AST_AND)
		return (exec_and(ast, shell));
	if (ast->type == AST_OR)
		return (exec_or(ast, shell));
	if (ast->type == AST_PIPE)
		return (exec_pipe(ast, shell));
	if (ast->type == AST_SUBSHELL)
		return (exec_subshell(ast, shell));
	return (EC_FAILURE);
}
