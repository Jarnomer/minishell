/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/01 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include <minishell.h>

typedef struct s_lexer
{
	const char	*input;
	size_t		pos;
	size_t		len;
	t_vec		tokens;
	t_err		error;
}	t_lexer;

t_lexer	lexer_new(const char *input);
void	lexer_free(t_lexer *lex);
bool	lexer_error(t_lexer *lex, void (*del)(void *), void *ptr);
bool	lexer_tokenize(t_lexer *lex);

t_token	*token_new(t_token_type type, char *value);
void	token_free(void *token);

bool	lexer_read_operator(t_lexer *lex);
bool	lexer_read_word(t_lexer *lex);

char	lexer_peek(t_lexer *lex);
char	lexer_peek_next(t_lexer *lex);
void	lexer_advance(t_lexer *lex);
void	lexer_skip_ws(t_lexer *lex);

#endif
