/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_operator.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jankku <jankku@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 00:00:00 by jankku            #+#    #+#             */
/*   Updated: 2025/01/01 00:00:00 by jankku           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static bool	lexer_add_double_op(t_lexer *lex, t_token_type type, char *str)
{
	t_token	*tok;

	lexer_advance(lex);
	lexer_advance(lex);
	tok = token_new(type, safe_strdup(str));
	return (vec_push(&lex->tokens, tok));
}

static bool	lexer_read_double_op(t_lexer *lex, char c, char next)
{
	if (c == '|' && next == '|')
		return (lexer_add_double_op(lex, TOK_OR, "||"));
	if (c == '&' && next == '&')
		return (lexer_add_double_op(lex, TOK_AND, "&&"));
	if (c == '<' && next == '<')
		return (lexer_add_double_op(lex, TOK_HEREDOC, "<<"));
	if (c == '>' && next == '>')
		return (lexer_add_double_op(lex, TOK_APPEND, ">>"));
	return (false);
}

static t_token_type	lexer_get_single_type(char c)
{
	if (c == '|')
		return (TOK_PIPE);
	if (c == '<')
		return (TOK_REDIR_IN);
	if (c == '>')
		return (TOK_REDIR_OUT);
	if (c == '(')
		return (TOK_LPAREN);
	if (c == ')')
		return (TOK_RPAREN);
	return (TOK_EOF);
}

bool	lexer_read_operator(t_lexer *lex)
{
	char			c;
	char			next;
	t_token_type	type;
	t_token			*tok;

	c = lexer_peek(lex);
	next = lexer_peek_next(lex);
	if (lexer_read_double_op(lex, c, next))
		return (true);
	type = lexer_get_single_type(c);
	if (type == TOK_EOF)
	{
		print_error_token("&");
		return (lexer_error(lex, NULL, NULL));
	}
	tok = token_new(type, safe_substr(lex->input, lex->pos, 1));
	lexer_advance(lex);
	return (vec_push(&lex->tokens, tok));
}
