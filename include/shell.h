/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/01 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H

# include <libft.h>
# include <utils.h>
# include <error.h>
# include <env.h>

# include <stdbool.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <errno.h>
# include <stdio.h>
# include <fcntl.h>
# include <signal.h>
# include <dirent.h>
# include <sys/wait.h>
# include <sys/stat.h>

# include <readline/readline.h>
# include <readline/history.h>

# define PROMPT 	C_GREEN "minishell" C_PURPLE "$ " C_RESET
# define METACHAR	"|<>&()"

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
