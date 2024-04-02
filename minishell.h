/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 17:35:47 by vkinaret          #+#    #+#             */
/*   Updated: 2024/03/28 20:01:13 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define MSG_SYNX		"syntax error near unexpected token"
# define MSG_CMD		"command not found"
# define MSG_PERM		"Permission denied"
# define MSG_FLDR		"Is a directory"
# define MSG_FILE		"No such file or directory"
# define MSG_MEM		"Out of memory"
# define MSG_FORK		"Could not fork"
# define MSG_PIPE		"Could not pipe"
# define BR				"\033[1;31m"
# define Y				"\033[0;33m"
# define T				"\033[0m"

# include "libft/libft.h"
# include <errno.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <fcntl.h>
# include <string.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_shell	t_shell;

enum e_errcodes
{
	NOERROR,
	ERR_FILE,
	ERR_PERM = 126,
	ERR_CMD,
	ERR_SIG,
	ERR_SYNX = 258
};

typedef enum e_checker
{
	FAILURE =	-1,
	SUCCESS =	0,
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

typedef struct	s_module
{
	char			*input;
	char			**cmd;
	char			*infile;
	int				indirect;
	char			*outfile;
	int				outdirect;
	int				redirect[2];
	t_parser		*parse;
	t_shell			*ms;
	struct s_module	*next;
}	t_module;

typedef struct	s_descriptors
{
	int	in;
	int	out;
	int	pipe[2];
}	t_descriptors;

typedef struct	s_shell
{
	char			*prompt;
	char			*input;
	char			*output;
	char			**envp;
	int				envp_size;
	t_module		*mods;
	t_descriptors	*fds;
	int				cmds;
	int				excode;
}				t_shell;

//parser.c
void	parse_inputs(t_module **lst, t_shell *ms);

//builtin.c
int		check_if_builtin(t_shell *ms, char *cmd);

//builtin2.c
void	builtin_cd(t_shell *ms, char *cmd);

//envp.c
char	**init_envp(int i, int size, t_shell *ms);
void	envp_update(t_shell *ms, char *content);
void	envp_add(t_shell *ms, char *content);
void	envp_remove(t_shell *ms, char *content);
void	envp_print(char **envp, int envp_size, int i, int flag);

//history.c

//free.c OK!
void	free_struct(t_shell *ms);
void	free_modules(t_module **lst);
void	free_parser(t_parser **lst);
void	free_array(char **array);
void	close_fds(t_descriptors *fds);

//init.c OK!
void	init_minishell(t_shell *ms);
void	init_fds(t_descriptors *fds);
void	init_modules(char *input, t_shell *ms);

//error.c
void	exit_error(int errcode, char *errmsg, t_shell *ms);
void	error_logger(char *msg1, char *msg2, char *msg3);
int		invalid_syntax(char *input, t_module *mod, t_shell *ms);

//safe_utils.c
void	*safe_calloc(size_t n, t_shell *ms);
void	safe_strdup(char **dst, char *src, t_shell *ms);
void	safe_substr(char **dst, char *stt, char *end, t_shell *ms);
void	safe_strtrim(char **src, char *set, t_shell *ms);
void	safe_strjoin(char **dst, char *s1, char *s2, t_shell *ms);
void	safe_fn_error(t_shell *ms);

#endif
