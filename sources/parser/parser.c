/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jankku <jankku@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 00:00:00 by jankku            #+#    #+#             */
/*   Updated: 2025/01/01 00:00:00 by jankku           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parser.h>

t_parser	parser_new(t_vec *tokens)
{
	t_parser	p;

	p.tokens = tokens;
	p.pos = 0;
	p.error = ERR_NONE;
	return (p);
}

void	*parser_error(t_parser *p, void (*del)(void *), void *ptr)
{
	p->error = ERR_SYNTAX;
	if (del)
		del(ptr);
	return (NULL);
}

t_ast	*parser_parse(t_parser *p)
{
	t_ast	*ast;

	if (!p || !p->tokens || p->tokens->len == 0)
		return (NULL);
	if (parser_check(p, TOK_EOF))
		return (NULL);
	ast = parse_command_line(p);
	if (!ast)
		return (NULL);
	if (!parser_check(p, TOK_EOF))
		return (parser_error(p, ast_free, ast));
	return (ast);
}
