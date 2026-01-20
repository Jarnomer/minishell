/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/01 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <debug.h>

static void	print_redir(t_redir *redir, int depth)
{
	print_debug_indent(depth);
	printf("redir: %s%s%s %s%s%s",
		DBG_PURPLE, redir_type_str(redir->type), DBG_RESET,
		DBG_CYAN, redir->target, DBG_RESET);
	if (redir->type == REDIR_HEREDOC && redir->quoted)
		printf(" %s[quoted]%s", DBG_YELLOW, DBG_RESET);
	printf("\n");
}

static void	print_redirs(t_vec *redirs, int depth)
{
	t_redir	*redir;
	size_t	i;

	i = 0;
	while (i < redirs->len)
	{
		redir = vec_get(redirs, i);
		print_redir(redir, depth);
		i++;
	}
}

static void	print_cmd_args(t_cmd *cmd, int depth)
{
	size_t	i;

	print_debug_indent(depth);
	printf("args: %s[%s", DBG_PURPLE, DBG_RESET);
	i = 0;
	while (i < cmd->args.len)
	{
		printf("%s%s%s", DBG_CYAN, (char *)vec_get(&cmd->args, i), DBG_RESET);
		if (i + 1 < cmd->args.len)
			printf(", ");
		i++;
	}
	printf("%s]%s\n", DBG_PURPLE, DBG_RESET);
	print_redirs(&cmd->redirs, depth);
}

void	debug_print_ast(t_ast *node, int depth)
{
	if (!node)
		return ;
	print_debug_indent(depth);
	printf("%s(%s)%s\n", DBG_GREEN, ast_type_str(node->type), DBG_RESET);
	if (node->type == AST_CMD && node->cmd)
		print_cmd_args(node->cmd, depth + 1);
	if (node->type == AST_SUBSHELL)
		print_redirs(&node->redirs, depth + 1);
	if (node->left)
		debug_print_ast(node->left, depth + 1);
	if (node->right)
		debug_print_ast(node->right, depth + 1);
}
