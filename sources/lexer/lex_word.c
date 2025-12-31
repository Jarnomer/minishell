/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_word.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jankku <jankku@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 00:00:00 by jankku            #+#    #+#             */
/*   Updated: 2025/01/01 00:00:00 by jankku           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lexer.h>

static void	lexer_join_segment(char **word, char *segment)
{
	char	*tmp;

	if (*word)
	{
		tmp = safe_strjoin(*word, segment);
		free(*word);
		free(segment);
		*word = tmp;
	}
	else
		*word = segment;
}

static bool	lexer_read_quoted(t_lexer *lex, char quote, char **word)
{
	char	*segment;
	size_t	start;

	start = lex->pos;
	lexer_advance(lex);
	while (lexer_peek(lex) && lexer_peek(lex) != quote)
		lexer_advance(lex);
	if (lexer_peek(lex) != quote)
		return (lexer_error(lex, NULL, NULL));
	lexer_advance(lex);
	segment = safe_substr(lex->input, start, lex->pos - start);
	lexer_join_segment(word, segment);
	return (true);
}

static bool	lexer_read_unquoted(t_lexer *lex, char **word)
{
	char	*segment;
	size_t	start;
	char	c;

	start = lex->pos;
	c = lexer_peek(lex);
	while (c && !ft_isspace(c) && !is_quote(c) && !is_metachar(c))
	{
		lexer_advance(lex);
		c = lexer_peek(lex);
	}
	if (lex->pos == start)
		return (true);
	segment = safe_substr(lex->input, start, lex->pos - start);
	lexer_join_segment(word, segment);
	return (true);
}

static bool	lexer_process_char(t_lexer *lex, char c, char **word)
{
	if (is_quote(c))
		return (lexer_read_quoted(lex, c, word));
	return (lexer_read_unquoted(lex, word));
}

bool	lexer_read_word(t_lexer *lex)
{
	char	*word;
	char	c;
	t_token	*tok;

	word = NULL;
	c = lexer_peek(lex);
	while (c && !ft_isspace(c) && !is_metachar(c))
	{
		if (!lexer_process_char(lex, c, &word))
			return (lexer_error(lex, free, word));
		c = lexer_peek(lex);
	}
	if (word)
	{
		tok = token_new(TOK_WORD, word);
		vec_push(&lex->tokens, tok);
	}
	return (true);
}
