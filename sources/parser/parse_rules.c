/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_rules.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/01 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parser.h>

static t_ast	*parse_pipeline(t_parser *p)
{
	t_ast	*left;
	t_ast	*right;

	left = parse_command(p);
	if (!left)
		return (NULL);
	while (parser_match(p, TOK_PIPE))
	{
		right = parse_command(p);
		if (!right)
			return (parser_error(p, ast_free, left));
		left = ast_new_binary(AST_PIPE, left, right);
	}
	return (left);
}

static t_ast_type	get_and_or_type(t_parser *p)
{
	if (parser_match(p, TOK_AND))
		return (AST_AND);
	if (parser_match(p, TOK_OR))
		return (AST_OR);
	return (AST_CMD);
}

static t_ast	*parse_and_or(t_parser *p)
{
	t_ast_type	type;
	t_ast		*left;
	t_ast		*right;

	left = parse_pipeline(p);
	if (!left)
		return (NULL);
	type = get_and_or_type(p);
	while (type != AST_CMD)
	{
		right = parse_pipeline(p);
		if (!right)
			return (parser_error(p, ast_free, left));
		left = ast_new_binary(type, left, right);
		type = get_and_or_type(p);
	}
	return (left);
}

t_ast	*parse_command_line(t_parser *p)
{
	return (parse_and_or(p));
}
