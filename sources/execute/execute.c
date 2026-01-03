/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/01 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <execute.h>

t_exec	exec_new(t_shell *shell)
{
	t_exec	ctx;

	ctx.shell = shell;
	ctx.lex = NULL;
	ctx.ast = NULL;
	return (ctx);
}

void	exec_cleanup(t_exec *ctx)
{
	if (ctx->lex)
	{
		lexer_free(ctx->lex);
		ctx->lex = NULL;
	}
	if (ctx->ast)
	{
		close_heredocs(ctx->ast);
		ast_free(ctx->ast);
		ctx->ast = NULL;
	}
}

static t_ast	*parse_input(t_exec *ctx)
{
	t_parser	parser;
	t_token		*err_tok;
	t_ast		*ast;

	err_tok = parser_validate(&ctx->lex->tokens);
	if (err_tok)
		return (exec_error_tok(ctx, err_tok->value));
	parser = parser_new(&ctx->lex->tokens);
	ast = parser_parse(&parser);
	if (!ast && parser.error != ERR_NONE)
		return (exec_error_tok(ctx, NULL));
	ctx->ast = ast;
	return (ast);
}

void	execute_shell(t_shell *shell, char *line)
{
	t_exec	ctx;
	t_lexer	lex;

	reset_signal();
	ctx = exec_new(shell);
	lex = lexer_new(line);
	ctx.lex = &lex;
	if (!lexer_tokenize(&lex))
	{
		shell->exit_status = EC_SYNTAX;
		lexer_free(&lex);
		return ;
	}
	if (!parse_input(&ctx))
		return ((void)exec_cleanup(&ctx));
	expand_ast(ctx.ast, shell);
	if (collect_heredocs(ctx.ast, shell) == -1)
		return ((void)exec_cleanup(&ctx));
	shell->exit_status = exec_ast(ctx.ast, shell);
	exec_cleanup(&ctx);
}
