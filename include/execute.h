/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/01 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

# include <shell.h>
# include <builtin.h>
# include <lexer.h>
# include <parser.h>
# include <expand.h>
# include <sig.h>

typedef struct s_exec
{
	t_shell	*shell;
	t_lexer	*lex;
	t_ast	*ast;
}	t_exec;

t_exec	exec_new(t_shell *shell);
void	exec_cleanup(t_exec *ctx);
void	execute_shell(t_shell *shell, char *line);

int		exec_ast(t_ast *ast, t_shell *shell);
int		exec_simple_cmd(t_cmd *cmd, t_shell *shell);
int		exec_pipe(t_ast *ast, t_shell *shell);
int		exec_subshell(t_ast *ast, t_shell *shell);

int		apply_redirs(t_vec *redirs);
int		save_std_fds(int saved_fds[2]);
void	restore_std_fds(int saved_fds[2]);

int		open_redir_file(t_redir *redir);
int		collect_heredocs(t_ast *ast, t_shell *shell);
void	close_heredocs(t_ast *ast);
char	*append_heredoc(char *content, char *line);

void	*exec_error_tok(t_exec *ctx, char *tok);

char	*resolve_path(const char *cmd, t_vec *env);
bool	is_direct_path(const char *cmd);

#endif
