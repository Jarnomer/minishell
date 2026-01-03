/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_ast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/01 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parser.h>

t_ast	*ast_new(t_ast_type type)
{
	t_ast	*node;

	node = safe_calloc(sizeof(t_ast));
	node->redirs = vec_new(0);
	node->type = type;
	return (node);
}

void	ast_free(void *ptr)
{
	t_ast	*node;

	node = (t_ast *)ptr;
	if (!node)
		return ;
	if (node->cmd)
		cmd_free(node->cmd);
	vec_free(&node->redirs, redir_free);
	if (node->left)
		ast_free(node->left);
	if (node->right)
		ast_free(node->right);
	free(node);
}

t_ast	*ast_new_cmd(t_cmd *cmd)
{
	t_ast	*node;

	node = ast_new(AST_CMD);
	node->cmd = cmd;
	return (node);
}

t_ast	*ast_new_binary(t_ast_type type, t_ast *left, t_ast *right)
{
	t_ast	*node;

	node = ast_new(type);
	node->left = left;
	node->right = right;
	return (node);
}
