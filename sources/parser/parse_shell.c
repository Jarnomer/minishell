/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_shell.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/01 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parser.h>

static t_redir	*parse_redirection(t_parser *p)
{
	t_token			*op_tok;
	t_token			*target_tok;
	t_redir_type	type;
	bool			quoted;

	op_tok = parser_advance(p);
	if (!parser_check(p, TOK_WORD))
		return (parser_error(p, NULL, NULL));
	target_tok = parser_advance(p);
	type = token_to_redir_type(op_tok->type);
	quoted = has_quotes(target_tok->value);
	return (redir_new(type, safe_strdup(target_tok->value), quoted));
}

static int	parse_token(t_cmd *cmd, t_parser *p)
{
	t_token	*tok;
	t_redir	*redir;

	tok = parser_peek(p);
	if (tok->type == TOK_WORD)
	{
		cmd_add_arg(cmd, safe_strdup(tok->value));
		parser_advance(p);
		return (1);
	}
	if (!is_redir_token(tok->type))
		return (0);
	redir = parse_redirection(p);
	if (!redir)
		return (-1);
	cmd_add_redir(cmd, redir);
	return (1);
}

static t_ast	*parse_simple_command(t_parser *p)
{
	t_cmd	*cmd;
	t_token	*tok;
	int		result;
	bool	has_content;

	cmd = cmd_new();
	has_content = false;
	tok = parser_peek(p);
	while (tok && tok->type != TOK_EOF)
	{
		result = parse_token(cmd, p);
		if (result == -1)
			return (parser_error(p, cmd_free, cmd));
		if (result == 0)
			break ;
		has_content = true;
		tok = parser_peek(p);
	}
	if (!has_content)
		return (parser_error(p, cmd_free, cmd));
	return (ast_new_cmd(cmd));
}

static t_ast	*parse_subshell(t_parser *p)
{
	t_ast	*node;
	t_ast	*inner;
	t_redir	*redir;

	if (!parser_match(p, TOK_LPAREN))
		return (NULL);
	inner = parse_command_line(p);
	if (!inner)
		return (parser_error(p, NULL, NULL));
	if (!parser_match(p, TOK_RPAREN))
		return (parser_error(p, ast_free, inner));
	node = ast_new(AST_SUBSHELL);
	node->left = inner;
	while (parser_peek(p) && is_redir_token(parser_peek(p)->type))
	{
		redir = parse_redirection(p);
		if (!redir)
			return (parser_error(p, ast_free, node));
		vec_push(&node->redirs, redir);
	}
	return (node);
}

t_ast	*parse_command(t_parser *p)
{
	if (parser_check(p, TOK_LPAREN))
		return (parse_subshell(p));
	else
		return (parse_simple_command(p));
}
