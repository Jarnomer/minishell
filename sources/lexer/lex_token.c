/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jankku <jankku@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 00:00:00 by jankku            #+#    #+#             */
/*   Updated: 2025/01/01 00:00:00 by jankku           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lexer.h>

t_token	*token_new(t_token_type type, char *value)
{
	t_token	*tok;

	tok = safe_calloc(sizeof(t_token));
	tok->type = type;
	tok->value = value;
	return (tok);
}

void	token_free(void *token)
{
	t_token	*tok;

	tok = (t_token *)token;
	if (!tok)
		return ;
	if (tok->value)
		free(tok->value);
	free(tok);
}

void	token_add_eof(t_lexer *lex, t_token *eof)
{
	vec_push(&lex->tokens, eof);
}
