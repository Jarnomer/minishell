/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jankku <jankku@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 00:00:00 by jankku            #+#    #+#             */
/*   Updated: 2025/01/01 00:00:00 by jankku           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

# include <minishell.h>
# include <lexer.h>
# include <parser.h>
# include <expand.h>

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
