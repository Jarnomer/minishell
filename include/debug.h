/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/01 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEBUG_H
# define DEBUG_H

# include <shell.h>
# include <lexer.h>
# include <parser.h>
# include <expand.h>

void		run_debug(t_shell *shell);

void		debug_print_lexer(t_lexer *lex);
void		debug_print_ast(t_ast *node, int depth);

void		print_debug_header(const char *title, const char *input);
void		print_debug_footer(void);
void		print_debug_indent(int depth);

const char	*token_type_str(t_token_type type);
const char	*ast_type_str(t_ast_type type);
const char	*redir_type_str(t_redir_type type);

#endif
