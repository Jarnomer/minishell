/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jankku <jankku@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 00:00:00 by jankku            #+#    #+#             */
/*   Updated: 2025/01/01 00:00:00 by jankku           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <debug.h>

static void	print_redirs(t_vec *redirs, int depth)
{
	t_redir	*redir;
	size_t	i;

	i = 0;
	while (i < redirs->len)
	{
		redir = vec_get(redirs, i);
		print_debug_indent(depth);
		printf("redir: %s %s", redir_type_str(redir->type), redir->target);
		if (redir->type == REDIR_HEREDOC && redir->quoted)
			printf(" (quoted)");
		printf("\n");
		i++;
	}
}

static void	print_cmd(t_cmd *cmd, int depth)
{
	size_t	i;

	print_debug_indent(depth);
	printf("args: [");
	i = 0;
	while (i < cmd->args.len)
	{
		printf("%s", (char *)vec_get(&cmd->args, i));
		if (i + 1 < cmd->args.len)
			printf(", ");
		i++;
	}
	printf("]\n");
	print_redirs(&cmd->redirs, depth);
}

void	debug_print_ast(t_ast *node, int depth)
{
	if (!node)
		return ;
	print_debug_indent(depth);
	printf("(%s)\n", ast_type_str(node->type));
	if (node->type == AST_CMD && node->cmd)
		print_cmd(node->cmd, depth + 1);
	if (node->type == AST_SUBSHELL)
		print_redirs(&node->redirs, depth + 1);
	if (node->left)
		debug_print_ast(node->left, depth + 1);
	if (node->right)
		debug_print_ast(node->right, depth + 1);
}
