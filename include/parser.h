/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/01 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <shell.h>

typedef struct s_parser
{
	t_vec	*tokens;
	size_t	pos;
	t_err	error;
}	t_parser;

t_parser		parser_new(t_vec *tokens);
void			*parser_error(t_parser *p, void (*del)(void *), void *ptr);
t_ast			*parser_parse(t_parser *p);

t_token			*parser_validate(t_vec *tokens);
t_ast			*parse_command_line(t_parser *p);
t_ast			*parse_command(t_parser *p);

t_ast			*ast_new(t_ast_type type);
void			ast_free(void *ptr);
t_ast			*ast_new_cmd(t_cmd *cmd);
t_ast			*ast_new_binary(t_ast_type type, t_ast *left, t_ast *right);

t_cmd			*cmd_new(void);
void			cmd_free(void *ptr);
void			cmd_add_arg(t_cmd *cmd, char *arg);

t_redir			*redir_new(t_redir_type type, char *target, bool quoted);
void			redir_free(void *redir);
void			cmd_add_redir(t_cmd *cmd, t_redir *redir);
bool			is_redir_token(t_token_type type);
t_redir_type	token_to_redir_type(t_token_type type);

t_token			*parser_peek(t_parser *p);
t_token			*parser_advance(t_parser *p);
bool			parser_check(t_parser *p, t_token_type type);
bool			parser_match(t_parser *p, t_token_type type);
bool			is_bin_op(t_token_type type);

#endif
