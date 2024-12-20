/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 17:35:47 by vkinaret          #+#    #+#             */
/*   Updated: 2024/05/16 19:29:36 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <libft.h>
# include <error.h>

# include <stdbool.h>
# include <fcntl.h>
# include <stdio.h>
# include <errno.h>
# include <string.h>
# include <dirent.h>
# include <termios.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <readline/readline.h>
# include <readline/history.h>

# define BR		"\001\033[1;31m\002"
# define Y		"\001\033[0;33m\002"
# define T		"\001\033[0m\002"
# define V		"\001\033[35m\002"
# define G		"\001\033[32m\002"

# define PERMS	0664

extern int	g_signal;

typedef enum e_checker
{
	ALLOCATE = 10,
	ALLOCATED,
}	t_checker;

typedef enum e_signal
{
	SIG_PARENT,
	SIG_HEREDOC,
	SIG_CHILD
}	t_signal;

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
	APPEND,
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
}	t_syntax;

typedef struct s_parser
{
	char			*content;
	struct s_parser	*next;
	struct s_parser	*prev;
	bool			joinable;
	int				meta;
	int				mode;
}	t_parser;

typedef struct s_module
{
	char			*input;
	struct s_module	*next;
	t_parser		*infiles;
	t_parser		*outfiles;
	t_parser		*command;
	char			**cmd;
	int				outfd;
	int				infd;
}	t_module;

typedef struct s_shell
{
	char			**envp;
	char			*prompt;
	char			*input;
	int				exitcode;
	int				envp_size;
	int				pipefd[2];
	int				tempfd;
	int				forks;
	int				index;
	char			*cwd;
	pid_t			*pids;
	t_module		*mods;
	t_parser		*trash;
}	t_shell;

//			Initialization
void		init_shell(t_shell *ms);
int			init_modules(char *input, t_shell *ms);

//			Signals
void		init_signals(int mode);

//			Parsing
void		parse_modules(t_module **lst, t_shell *ms);
char		*parse_input(char *argv, t_parser *new, t_module *mod);
void		parse_argv(t_parser *new, t_module *mod, t_shell *ms);
void		parse_envps(t_parser *new, t_shell *ms);
void		parse_expands(t_module *mod, t_shell *ms);
int			parse_files(t_module *mod, t_shell *ms);

//			Parser Utils
void		preview_content(t_parser *prev, t_parser *new);
void		parser_append(t_parser **lst, t_parser *new);
int			parser_length(t_parser *lst);
t_parser	*parser_last(t_parser *lst);
void		parser_delone(t_parser *lst);

//			Parser Helpers
char		*find_breakpoint(char *argv);
bool		ft_hasspace(char *argv);
int			ft_isredirect(char c);
int			ft_ismeta(char c);

//			Child processes
void		execute_children(t_shell *ms);
void		redirect_fds(t_module *mod, t_shell *ms);
void		execute_command(t_module *mod, t_shell *ms);
void		wait_children(t_shell *ms);

//			Open files
t_parser	*open_infile(t_parser *infile, t_module *mod, t_shell *ms);
t_parser	*open_outfile(t_parser *outfile, t_module *mod, t_shell *ms);
void		open_heredocs(t_module *mod, t_shell *ms);

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

//			Builtin functions
void		builtin_echo(t_shell *ms, char **cmd);
void		builtin_cd(t_shell *ms, char **cmd, char *pwd, char *oldpwd);
void		builtin_env(t_shell *ms, int i, int j);
void		builtin_export(t_shell *ms, char **cmd, int i);
void		builtin_unset(t_shell *ms, char **cmd, int i);
void		builtin_pwd(t_shell *ms);
void		builtin_exit(t_shell *ms, char **cmd);

//			Builtin utils
bool		is_builtin(t_module *mod);
bool		is_builtin2(t_module *mod);
void		execute_builtin(t_shell *ms, t_module *mod);

//			Envp utils
void		envp_print(t_shell *ms, int i, int flag);
void		envp_update(t_shell *ms, char *content);
void		envp_add(t_shell *ms, char *content);
void		envp_remove(t_shell *ms, char *content);
char		*envp_exists(char *name, t_shell *ms);

#endif
