/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/01 00:00:00 by jmertane         ###   ########.fr       */
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
