/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jankku <jankku@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 00:00:00 by jankku            #+#    #+#             */
/*   Updated: 2025/01/01 00:00:00 by jankku           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <debug.h>

static t_ast	*debug_parse(t_lexer *lex)
{
	t_parser	parser;
	t_ast		*ast;
	t_token		*err_tok;

	err_tok = parser_validate(&lex->tokens);
	if (err_tok)
	{
		print_error_token(err_tok->value);
		return (NULL);
	}
	parser = parser_new(&lex->tokens);
	ast = parser_parse(&parser);
	if (!ast && parser.error != ERR_NONE)
		print_error_token(NULL);
	return (ast);
}

static void	debug_process_line(t_shell *shell, char *line)
{
	t_lexer	lex;
	t_ast	*ast;

	lex = lexer_new(line);
	if (!lexer_tokenize(&lex))
		return (print_error("ERR_MSG_QUOTE"), lexer_free(&lex));
	print_debug_header("1. LEXER (tokenizing)", line);
	debug_print_lexer(&lex);
	print_debug_footer();
	ast = debug_parse(&lex);
	if (!ast)
		return (lexer_free(&lex));
	print_debug_header("2. PARSER (before expand)", line);
	debug_print_ast(ast, 0);
	print_debug_footer();
	expand_ast(ast, shell);
	print_debug_header("3. RESULT (after expand)", line);
	debug_print_ast(ast, 0);
	print_debug_footer();
	lexer_free(&lex);
	ast_free(ast);
}

void	run_debug_mode(t_shell *shell)
{
	char	*line;

	while (1)
	{
		line = readline(PROMPT);
		if (!line)
		{
			printf("exit\n");
			break ;
		}
		if (*line)
		{
			add_history(line);
			debug_process_line(shell, line);
		}
		free(line);
	}
}
