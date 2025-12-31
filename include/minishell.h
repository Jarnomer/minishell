/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jankku <jankku@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 00:00:00 by jankku            #+#    #+#             */
/*   Updated: 2025/01/01 00:00:00 by jankku           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <libft.h>
# include <error.h>
# include <utils.h>
# include <env.h>
# include <vec.h>

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <stdbool.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <errno.h>

# include <readline/readline.h>
# include <readline/history.h>

# define PROMPT "minishell$ "
# define METACHAR "|<>&()"

typedef enum e_token_type
{
	TOK_WORD,
	TOK_PIPE,
	TOK_REDIR_IN,
	TOK_REDIR_OUT,
	TOK_HEREDOC,
	TOK_APPEND,
	TOK_AND,
	TOK_OR,
	TOK_LPAREN,
	TOK_RPAREN,
	TOK_EOF
}	t_token_type;

typedef enum e_redir_type
{
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	REDIR_HEREDOC
}	t_redir_type;

typedef enum e_ast_type
{
	AST_CMD,
	AST_PIPE,
	AST_AND,
	AST_OR,
	AST_SUBSHELL
}	t_ast_type;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
}	t_token;

typedef struct s_redir
{
	t_redir_type	type;
	char			*target;
	bool			quoted;
	int				fd;
}	t_redir;

typedef struct s_cmd
{
	t_vec	args;
	t_vec	redirs;
}	t_cmd;

typedef struct s_ast
{
	t_ast_type		type;
	t_cmd			*cmd;
	struct s_ast	*left;
	struct s_ast	*right;
	t_vec			redirs;
}	t_ast;

typedef struct s_shell
{
	t_vec	env;
	int		exit_status;
	bool	interactive;
	bool	running;
}	t_shell;

#endif
