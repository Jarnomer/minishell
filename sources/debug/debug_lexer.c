/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_lexer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/01 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <debug.h>

static bool	has_unquoted_wildcard(const char *str)
{
	t_quote_state	state;

	state = Q_NONE;
	while (*str)
	{
		if (*str == '\'' || *str == '"')
			state = update_quote_state(*str, state);
		else if (*str == '*' && state == Q_NONE)
			return (true);
		str++;
	}
	return (false);
}

static void	print_token_flags(t_token *tok)
{
	bool	is_quoted;
	bool	is_wildcard;

	if (tok->type != TOK_WORD || !tok->value)
		return ;
	is_quoted = has_quotes(tok->value);
	is_wildcard = has_unquoted_wildcard(tok->value);
	if (is_quoted || is_wildcard)
		printf("  %s[", DBG_YELLOW);
	if (is_quoted)
		printf("quoted");
	if (is_quoted && is_wildcard)
		printf(", ");
	if (is_wildcard)
		printf("wildcard");
	if (is_quoted || is_wildcard)
		printf("]%s", DBG_RESET);
}

static void	print_token(t_token *tok)
{
	if (!tok)
	{
		print_debug_indent(0);
		printf("%s(null token)%s\n", DBG_YELLOW, DBG_RESET);
		return ;
	}
	print_debug_indent(0);
	printf("  %s%-10s%s:", DBG_GREEN, token_type_str(tok->type), DBG_RESET);
	if (tok->value)
		printf(" %s%s%s", DBG_CYAN, tok->value, DBG_RESET);
	print_token_flags(tok);
	printf("\n");
}

void	debug_print_lexer(t_lexer *lex)
{
	t_token	*tok;
	size_t	i;

	print_debug_indent(0);
	printf("Tokens: %s%zu%s\n", DBG_CYAN, lex->tokens.len, DBG_RESET);
	i = 0;
	while (i < lex->tokens.len)
	{
		tok = vec_get(&lex->tokens, i);
		print_token(tok);
		i++;
	}
}
