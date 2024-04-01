/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 17:35:47 by vkinaret          #+#    #+#             */
/*   Updated: 2024/04/01 18:45:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include "error.h"
# include "styles.h"

# include <errno.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <fcntl.h>
# include <string.h>
# include <errno.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_shell	t_shell;

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
	struct s_parser	*next;
}	t_parser;

typedef struct s_module
{
	char			*input;
	char			**cmd;
	char			*infile;
	int				indirect;
	char			*outfile;
	int				outdirect;
	t_parser		*parse;
	t_shell			*ms;
	struct s_module	*next;
}	t_module;

typedef struct s_descriptors
{
	int	in;
	int	out;
	int	pipe[2];
}	t_descriptors;

typedef struct s_shell
{
	char			**envp;
	char			*prompt;
	char			*input;
	t_module		*mods;
	t_descriptors	*fds;
	int				cmds;
	int				excode;
}	t_shell;

// Init functions
void	init_shell(t_shell *ms);
char	**init_environ(void);
void	init_modules(char *input, t_shell *ms);

// parser WIP
void	parse_inputs(t_module **lst, t_shell *ms);

// Free functions and utils
void	free_runtime(t_shell *ms);
void	self_destruct(t_shell *ms);
void	close_fds(t_descriptors **fds);
void	free_douple(char ***arr);
void	free_single(char **str);

// Error functions and utils
void	exit_error(int errcode, char *errmsg, t_shell *ms);
void	error_logger(char *msg1, char *msg2, char *msg3);
int		invalid_syntax(char *input, t_module *mod, t_shell *ms);

// Safety wrapper functions
void	*safe_calloc(size_t n, t_shell *ms);
void	safe_strdup(char **dst, char *src, t_shell *ms);
void	safe_substr(char **dst, char *stt, char *end, t_shell *ms);
void	safe_strtrim(char **src, char *set, t_shell *ms);
void	safe_strjoin(char **dst, char *s1, char *s2, t_shell *ms);
void	safe_fn_error(t_shell *ms);
#endif
