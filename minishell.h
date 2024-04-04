/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 17:35:47 by vkinaret          #+#    #+#             */
/*   Updated: 2024/04/04 17:17:44 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include "error.h"
# include "styles.h"

# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <fcntl.h>
# include <string.h>
# include <errno.h>
#include <sys/_types/_pid_t.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef enum e_checker
{
	SUCCESS,
	FAILURE
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

typedef struct s_parser
{
	char			*content;
	int				mode;
	int				fd;
	struct s_parser	*next;
}	t_parser;

typedef struct s_module
{
	char			*input;
	t_parser		*infiles;
	t_parser		*outfiles;
	t_parser		*command;
	struct s_module	*next;
}	t_module;

typedef struct s_shell
{
	char			**envp;
	char			*prompt;
	char			*input;
	int				pipe[2];
	pid_t			*pids;
	int				excode;
	int				cmds;
	t_module		*mods;
}	t_shell;

// Init functions
void	init_shell(t_shell *ms);
char	**init_environ(void);
void	init_modules(char *input, t_shell *ms);

// parser WIP
void	parse_inputs(t_module **mod, t_shell *ms);
char	*handle_infile(char *input, int *mode, t_module *mod, t_shell *ms);
char	*handle_outfile(char *input, int *mode, t_module *mod, t_shell *ms);
char	*handle_command(char *input, t_module *mod, t_shell *ms);
char	assign_delimiter(char *argv);
char	*find_breakpoint(char *input, char c);
void	filter_quotes(char *content, char c, t_shell *ms);

// open functions
void	open_file(t_parser **lst, int mode);

// Free functions and utils
void	free_runtime(t_shell *ms, int errcode);
void	free_douple(char ***arr);
void	free_single(char **str);

// Error functions and utils
void	exit_error(int errcode, char *errmsg, t_shell *ms);
void	error_logger(char *msg1, char *msg2, char *msg3);
int		invalid_syntax(char *input, char c, t_shell *ms);

// Safety wrapper functions
void	*safe_calloc(size_t n, t_shell *ms);
void	safe_strdup(char **dst, char *src, t_shell *ms);
void	safe_substr(char **dst, char *stt, char *end, t_shell *ms);
void	safe_strtrim(char **src, char *set, t_shell *ms);
void	safe_strjoin(char **dst, char *s1, char *s2, t_shell *ms);
void	safe_fn_error(t_shell *ms);

// Miscellaneous utility functions
int		ft_isspace(char c);
int		ft_issyntax(char c);

#endif
