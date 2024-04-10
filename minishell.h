/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 17:35:47 by vkinaret          #+#    #+#             */
/*   Updated: 2024/04/09 19:18:09 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include "error.h"

# include <stdbool.h>
# include <fcntl.h>
# include <stdio.h>
# include <errno.h>
# include <string.h>
# include <dirent.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <readline/readline.h>
# include <readline/history.h>

# define BR		"\033[1;31m"
# define Y		"\033[0;33m"
# define T		"\033[0m"
# define V		"\033[35m"
# define G		"\033[32m"

# define FDLMT	241
# define PERMS	0664

typedef enum e_checker
{
	SUCCESS = 0,
	FAILURE = -1
}	t_checker;

typedef enum e_pipe
{
	RD_END = 0,
	WR_END = 1
}	t_pipe;

typedef enum e_redirect
{
	STDIN,
	STDOUT,
	STDERR,
	INFILE,
	HEREDOC,
	OUTFILE,
	APPEND
}	t_redirect;

typedef enum e_syntax
{
	PIPE = 124,
	INDIRECT = 60,
	OUTDIRECT = 62,
	SINGLEQUOTE = 39,
	DOUBLEQUOTE = 34,
	SPACE = 32
}	t_syntax;

typedef struct s_parser
{
	char			*content;
	int				mode;
	struct s_parser	*next;
}	t_parser;

typedef struct s_module
{
	char			*input;
	t_parser		*infiles;
	t_parser		*outfiles;
	t_parser		*command;
	int				outfd;
	int				infd;
	struct s_module	*next;
}	t_module;

typedef struct s_shell
{
	char			**envp;
	char			*prompt;
	char			*input;
	int				excode;
	int				envp_size;
	int				pipefd[2];
	int				tempfd;
	int				cmds;
	int				idx;
	pid_t			*pids;
	t_module		*mods;
}	t_shell;

// Initialization
void		init_shell(t_shell *ms);
int			init_modules(char *input, t_shell *ms);

// Parser
void		parse_inputs(t_module **lst, t_shell *ms);
void		parse_files(t_module **lst, t_shell *ms);
char		*parse_argument(char *argv, char c, t_parser **lst, t_shell *ms);
int			parser_length(t_parser	*file);
t_parser	*parser_last(t_parser *file);
char		assign_delimiter(char *argv);
char		*find_breakpoint(char *input, char c);
void		filter_quotes(char *content, char c, t_shell *ms);

// Child processes
void		execute_children(t_shell *ms);
void		redirect_fds(t_module *mod, t_shell *ms);
void		execute_command(t_module *mod, t_shell *ms);
void		wait_children(t_shell *ms);

// Open files
int			open_infile(t_module *mod, t_shell *ms);
int			open_outfile(t_module *mod, t_shell *ms);
int			open_heredoc(char *eof, t_shell *ms);

// Free memory
void		free_runtime(t_shell *ms);
void		free_exit(t_shell *ms);
void		close_fds(t_shell *ms);
void		free_double(char ***arr);
void		free_single(char **str);

// Error handling
void		error_exit(int errcode, char *msg1, char *msg2, t_shell *ms);
void		error_logger(char *msg1, char *msg2, char *msg3, t_shell *ms);
int			error_syntax(char *input, char c, t_shell *ms);
void		error_fatal(int errcode, char *errmsg, t_shell *ms);

// Safety wrappers
void		*safe_calloc(size_t n, t_shell *ms);
void		safe_strdup(char **dst, char *src, t_shell *ms);
void		safe_substr(char **dst, char *stt, char *end, t_shell *ms);
void		safe_strtrim(char **src, char *set, t_shell *ms);
void		safe_strjoin(char **dst, char *s1, char *s2, t_shell *ms);

// Utility functions
char		*executable_path(char *exec, t_shell *ms);
int			ft_isspace(char c);
int			ft_issyntax(char c);

// Envp functions
void		envp_print(char **envp, int envp_size, int i, int flag);
void		envp_update(t_shell *ms, char *content);
void		envp_add(t_shell *ms, char *content);
void		envp_remove(t_shell *ms, char *content);

// Builtin functions
int			is_builtin(t_shell *ms, char **cmd);
int			name_exists(t_shell *ms, char *name);
void		builtin_echo(t_shell *ms, char **cmd);
void		builtin_cd(t_shell *ms, char **cmd);
void		builtin_env(char **envp, int i, int j);
void		builtin_export(t_shell *ms, char **cmd, int i, int j);
void		builtin_unset(t_shell *ms, char **cmd, int i, int j);
void		builtin_pwd(t_shell *ms, char **envp);

//Exec test
void	execute_test(t_shell *ms);

#endif
