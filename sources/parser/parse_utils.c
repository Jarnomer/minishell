/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/01 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parser.h>

t_token	*parser_peek(t_parser *p)
{
	return (vec_get(p->tokens, p->pos));
}

t_token	*parser_advance(t_parser *p)
{
	t_token	*tok;

	tok = parser_peek(p);
	if (tok && tok->type != TOK_EOF)
		p->pos++;
	return (tok);
}

bool	parser_check(t_parser *p, t_token_type type)
{
	t_token	*tok;

	tok = parser_peek(p);
	if (!tok)
		return (false);
	return (tok->type == type);
}

bool	parser_match(t_parser *p, t_token_type type)
{
	if (parser_check(p, type))
	{
		parser_advance(p);
		return (true);
	}
	return (false);
}

bool	is_bin_op(t_token_type type)
{
	return (type == TOK_PIPE || type == TOK_AND || type == TOK_OR);
}
