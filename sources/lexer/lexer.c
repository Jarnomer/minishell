/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jankku <jankku@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 00:00:00 by jankku            #+#    #+#             */
/*   Updated: 2025/01/01 00:00:00 by jankku           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lexer.h>

t_lexer	lexer_new(const char *input)
{
	t_lexer	lex;

	lex.input = input;
	lex.pos = 0;
	lex.len = ft_strlen(input);
	lex.tokens = vec_new(0);
	lex.error = ERR_NONE;
	return (lex);
}

void	lexer_free(t_lexer *lex)
{
	if (!lex)
		return ;
	vec_free(&lex->tokens, token_free);
}

/*
** Set syntax error, optionally free pointer with deleter, return false
** Pass NULL for del and ptr if no cleanup needed
*/
bool	lexer_error(t_lexer *lex, void (*del)(void *), void *ptr)
{
	lex->error = ERR_SYNTAX;
	if (del)
		del(ptr);
	return (false);
}

bool	lexer_tokenize(t_lexer *lex)
{
	char	c;
	t_token	*eof;

	while (lex->pos < lex->len)
	{
		lexer_skip_ws(lex);
		c = lexer_peek(lex);
		if (c == '\0')
			break ;
		if (is_metachar(c))
		{
			if (!lexer_read_operator(lex))
				return (false);
		}
		else
		{
			if (!lexer_read_word(lex))
				return (false);
		}
	}
	eof = token_new(TOK_EOF, NULL);
	token_add_eof(lex, eof);
	return (lex->error == ERR_NONE);
}
