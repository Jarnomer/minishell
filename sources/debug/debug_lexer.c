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

static void	debug_print_token(t_token *tok)
{
	if (!tok)
	{
		printf("║   (null token)\n");
		return ;
	}
	printf("║   %-10s", token_type_str(tok->type));
	if (tok->value)
		printf(" %s", tok->value);
	printf("\n");
}

void	debug_print_lexer(t_lexer *lex)
{
	t_token	*tok;
	size_t	i;

	printf("║ Token count: %zu\n", lex->tokens.len);
	printf("╠══════════════════════════════════════════════════════════╣\n");
	printf("║ Tokens:\n");
	i = 0;
	while (i < lex->tokens.len)
	{
		tok = vec_get(&lex->tokens, i);
		debug_print_token(tok);
		i++;
	}
}
