/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 17:35:47 by vkinaret          #+#    #+#             */
/*   Updated: 2024/04/20 17:57:36 by jmertane         ###   ########.fr       */
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
# include <termios.h>

# define BR		"\033[1;31m"
# define Y		"\033[0;33m"
# define T		"\033[0m"
# define V		"\033[35m"
# define G		"\033[32m"

# define FDLMT	241
# define PERMS	0664

typedef enum e_checker
{
	FAILURE = -1,
	SUCCESS = 0,
	ALLOCATE = 10,
	ALLOCATED,
}	t_checker;

typedef enum e_pipe
{
	RD_END,
	WR_END
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
	DOLLAR = 36,
	INDIRECT = 60,
	OUTDIRECT = 62,
	SINGLEQUOTE = 39,
	DOUBLEQUOTE = 34,
	QUESTIONMARK = 63,
	EMPTY = 32
}	t_syntax;

typedef struct s_parser
{
	char			*content;
	int				mode;
	struct s_parser	*next;
	struct s_parser	*prev;
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
	int				forks;
	int				index;
	pid_t			*pids;
	t_module		*mods;
	t_parser		*trash;
}	t_shell;

//			Initialization
void		init_shell(t_shell *ms);
int			init_modules(char *input, t_shell *ms);

//			Parsers
void		parse_inputs(t_module **lst, t_shell *ms);
char		*parse_argv(char *input, t_module *mod, t_shell *ms);
void		parse_envp(t_parser *lst, int mode, t_shell *ms);

//			Parser utils
void		parser_append(t_parser **lst, t_parser *new);
int			parser_length(t_parser *lst);
t_parser	*parser_last(t_parser *lst);
void		parser_delone(t_parser *lst);

//			Parser helpers
char		assign_delimiter(char *argv);
char		*find_breakpoint(char *input, char c, int hdoc_flag);
void		filter_quotes(char *content, char c, bool *checker, t_shell *ms);

//			Child processes
void		execute_children(t_shell *ms);
void		redirect_fds(t_module *mod, t_shell *ms);
void		execute_command(t_module *mod, t_shell *ms);
void		wait_children(t_shell *ms);

//			Open files
int			open_infile(t_module *mod, t_shell *ms);
int			open_outfile(t_module *mod, t_shell *ms);
int			open_heredoc(t_parser *hdoc, t_shell *ms);

//			Free memory
void		free_runtime(t_shell *ms);
void		free_exit(t_shell *ms);
void		close_fds(t_shell *ms);
void		free_double(char ***arr);
void		free_single(char **str);

//			Error handling
void		error_exit(int errcode, char *msg1, char *msg2, t_shell *ms);
void		error_logger(char *msg1, char *msg2, char *msg3, t_shell *ms);
int			error_syntax(char *input, t_shell *ms);
void		error_fatal(int errcode, char *errmsg, t_shell *ms);

//			Safety wrappers
void		*safe_calloc(size_t n, t_shell *ms);
char		*safe_trash(char *str, int alloc_flag, t_shell *ms);
char		**safe_double(t_parser *lst, t_shell *ms);
void		safe_strdup(char **dst, char *src, t_shell *ms);
void		safe_substr(char **dst, char *stt, char *end, t_shell *ms);
void		safe_strtrim(char **src, char *set, t_shell *ms);
void		safe_strjoin(char **dst, char *s1, char *s2, t_shell *ms);

//			Utility functions
int			ft_isspace(char c);
int			ft_isredirect(char c);

//			Signal functions
void		init_signals(void);

//			Envp functions
void		envp_print(char **envp, int envp_size, int i, int flag);
void		envp_update(t_shell *ms, char *content);
void		envp_add(t_shell *ms, char *content);
void		envp_remove(t_shell *ms, char *content);
char		*envp_exists(char *name, t_shell *ms);

//			Builtin utils
bool		is_builtin(t_module *mod);
bool		is_builtin2(t_module *mod);
void		execute_builtin(t_shell *ms, t_module *mod);
int			name_exists(t_shell *ms, char *name);

//			Builtin functions
void		builtin_echo(char **cmd);
void		builtin_cd(t_shell *ms, char **cmd);
void		builtin_env(char **envp, int i, int j);
void		builtin_export(t_shell *ms, char **cmd, int i, int j);
void		builtin_unset(t_shell *ms, char **cmd, int i, int j);
void		builtin_pwd(t_shell *ms, char **envp);

#endif
