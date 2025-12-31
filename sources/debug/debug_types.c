/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_types.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jankku <jankku@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 00:00:00 by jankku            #+#    #+#             */
/*   Updated: 2025/01/01 00:00:00 by jankku           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <debug.h>

const char	*token_type_str(t_token_type type)
{
	if (type == TOK_WORD)
		return ("WORD");
	if (type == TOK_PIPE)
		return ("PIPE");
	if (type == TOK_REDIR_IN)
		return ("REDIR_IN");
	if (type == TOK_REDIR_OUT)
		return ("REDIR_OUT");
	if (type == TOK_HEREDOC)
		return ("HEREDOC");
	if (type == TOK_APPEND)
		return ("APPEND");
	if (type == TOK_AND)
		return ("AND");
	if (type == TOK_OR)
		return ("OR");
	if (type == TOK_LPAREN)
		return ("LPAREN");
	if (type == TOK_RPAREN)
		return ("RPAREN");
	if (type == TOK_EOF)
		return ("EOF");
	return ("UNKNOWN");
}

const char	*ast_type_str(t_ast_type type)
{
	if (type == AST_CMD)
		return ("CMD");
	if (type == AST_PIPE)
		return ("PIPE");
	if (type == AST_AND)
		return ("AND");
	if (type == AST_OR)
		return ("OR");
	if (type == AST_SUBSHELL)
		return ("SUBSHELL");
	return ("UNKNOWN");
}

const char	*redir_type_str(t_redir_type type)
{
	if (type == REDIR_IN)
		return ("<");
	if (type == REDIR_OUT)
		return (">");
	if (type == REDIR_APPEND)
		return (">>");
	if (type == REDIR_HEREDOC)
		return ("<<");
	return ("?");
}
