/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jankku <jankku@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 00:00:00 by jankku            #+#    #+#             */
/*   Updated: 2025/01/01 00:00:00 by jankku           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <execute.h>
#include <sig.h>

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
		return ;
	if (!parse_input(&ctx))
		return ;
	expand_ast(ctx.ast, shell);
	if (collect_heredocs(ctx.ast, shell) == -1)
	{
		exec_cleanup(&ctx);
		return ;
	}
	shell->exit_status = exec_ast(ctx.ast, shell);
	exec_cleanup(&ctx);
}
