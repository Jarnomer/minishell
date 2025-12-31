/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_valid.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jankku <jankku@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 00:00:00 by jankku            #+#    #+#             */
/*   Updated: 2025/01/01 00:00:00 by jankku           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parser.h>

/*
** Check: unmatched parentheses
*/
static t_token	*validate_parentheses(t_vec *tokens)
{
	int		depth;
	t_token	*tok;
	t_token	*last_open;
	size_t	i;

	depth = 0;
	last_open = NULL;
	i = 0;
	while (i < tokens->len)
	{
		tok = vec_get(tokens, i);
		if (tok->type == TOK_LPAREN)
		{
			depth++;
			last_open = tok;
		}
		else if (tok->type == TOK_RPAREN)
		{
			if (depth == 0)
				return (tok);
			depth--;
		}
		i++;
	}
	if (depth > 0)
		return (last_open);
	return (NULL);
}

/*
** Check: no leading binary operator (|, &&, ||)
** Check: no trailing binary operator or redirection
*/
static t_token	*validate_edges(t_vec *tokens)
{
	t_token	*first;
	t_token	*last;
	size_t	len;

	len = tokens->len;
	if (len < 2)
		return (NULL);
	first = vec_get(tokens, 0);
	if (is_bin_op(first->type))
		return (first);
	last = vec_get(tokens, len - 2);
	if (is_bin_op(last->type) || is_redir_token(last->type))
		return (last);
	return (NULL);
}

/*
** Check: no consecutive binary operators (cmd && || other)
** Check: no empty parentheses ()
** Check: no binary operator after open paren ((| cmd)
** Check: no binary operator before close paren (cmd |)
*/
static t_token	*validate_sequence(t_vec *tokens)
{
	t_token	*prev;
	t_token	*curr;
	size_t	i;

	i = 1;
	while (i < tokens->len)
	{
		prev = vec_get(tokens, i - 1);
		curr = vec_get(tokens, i);
		if (is_bin_op(prev->type) && is_bin_op(curr->type))
			return (curr);
		if (prev->type == TOK_LPAREN && curr->type == TOK_RPAREN)
			return (curr);
		if (prev->type == TOK_LPAREN && is_bin_op(curr->type))
			return (curr);
		if (is_bin_op(prev->type) && curr->type == TOK_RPAREN)
			return (curr);
		i++;
	}
	return (NULL);
}

/*
** Check: redirection must be followed by WORD
*/
static t_token	*validate_redirections(t_vec *tokens)
{
	t_token	*curr;
	t_token	*next;
	size_t	i;

	i = 0;
	while (i < tokens->len - 1)
	{
		curr = vec_get(tokens, i);
		next = vec_get(tokens, i + 1);
		if (is_redir_token(curr->type) && next->type != TOK_WORD)
			return (next);
		i++;
	}
	return (NULL);
}

/*
** Validates token stream before parsing.
** Returns NULL if valid, or pointer to offending token.
*/
t_token	*parser_validate(t_vec *tokens)
{
	t_token	*err_tok;

	if (!tokens || tokens->len == 0)
		return (NULL);
	err_tok = validate_edges(tokens);
	if (err_tok)
		return (err_tok);
	err_tok = validate_sequence(tokens);
	if (err_tok)
		return (err_tok);
	err_tok = validate_redirections(tokens);
	if (err_tok)
		return (err_tok);
	err_tok = validate_parentheses(tokens);
	if (err_tok)
		return (err_tok);
	return (NULL);
}
