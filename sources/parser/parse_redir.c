/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/01 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parser.h>

t_redir	*redir_new(t_redir_type type, char *target, bool quoted)
{
	t_redir	*redir;

	redir = safe_calloc(sizeof(t_redir));
	redir->target = target;
	redir->quoted = quoted;
	redir->type = type;
	redir->fd = -1;
	return (redir);
}

void	redir_free(void *ptr)
{
	t_redir	*redir;

	redir = (t_redir *)ptr;
	if (!redir)
		return ;
	if (redir->target)
		free(redir->target);
	free(redir);
}

void	cmd_add_redir(t_cmd *cmd, t_redir *redir)
{
	vec_push(&cmd->redirs, redir);
}

bool	is_redir_token(t_token_type type)
{
	return (type == TOK_REDIR_IN || type == TOK_REDIR_OUT
		|| type == TOK_HEREDOC || type == TOK_APPEND);
}

t_redir_type	token_to_redir_type(t_token_type type)
{
	if (type == TOK_REDIR_IN)
		return (REDIR_IN);
	if (type == TOK_REDIR_OUT)
		return (REDIR_OUT);
	if (type == TOK_APPEND)
		return (REDIR_APPEND);
	return (REDIR_HEREDOC);
}
