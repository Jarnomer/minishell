/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jankku <jankku@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 00:00:00 by jankku            #+#    #+#             */
/*   Updated: 2025/01/01 00:00:00 by jankku           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lexer.h>

char	lexer_peek(t_lexer *lex)
{
	if (lex->pos >= lex->len)
		return ('\0');
	return (lex->input[lex->pos]);
}

char	lexer_peek_next(t_lexer *lex)
{
	if (lex->pos + 1 >= lex->len)
		return ('\0');
	return (lex->input[lex->pos + 1]);
}

void	lexer_advance(t_lexer *lex)
{
	if (lex->pos < lex->len)
		lex->pos++;
}

void	lexer_skip_ws(t_lexer *lex)
{
	char	c;

	c = lexer_peek(lex);
	while (ft_isspace(c))
	{
		lexer_advance(lex);
		c = lexer_peek(lex);
	}
}
