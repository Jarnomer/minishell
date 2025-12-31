/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jankku <jankku@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 00:00:00 by jankku            #+#    #+#             */
/*   Updated: 2025/01/01 00:00:00 by jankku           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEBUG_H
# define DEBUG_H

# include <minishell.h>
# include <lexer.h>
# include <parser.h>
# include <expand.h>

void		run_debug_mode(t_shell *shell);

void		print_debug_header(const char *title, const char *input);
void		print_debug_footer(void);
void		print_debug_indent(int depth);

const char	*token_type_str(t_token_type type);
const char	*ast_type_str(t_ast_type type);
const char	*redir_type_str(t_redir_type type);

void		debug_print_lexer(t_lexer *lex);
void		debug_print_ast(t_ast *node, int depth);

#endif
