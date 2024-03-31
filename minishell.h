/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 17:35:47 by vkinaret          #+#    #+#             */
/*   Updated: 2024/03/31 14:39:46 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include "libft/libft.h"

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/_types/_size_t.h>

typedef struct s_shell	t_shell;

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
	char			*outfile;
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
	char			**envp;
	char			*prompt;
	char			*input;
	int				cmds;
	t_module		*mods;
	t_descriptors	*fds;
}	t_shell;

// initialization functions
void	init_shell(t_shell *ms);
char	**init_environ(void);
void	init_modules(char *input, t_shell *ms);

// parser WIP
void	parse_inputs(t_module **lst);

// main freeing functions
void	free_runtime(t_shell *ms);
void	self_destruct(t_shell *ms);
void	close_fds(t_descriptors **fds);

// these functions are for safe allocations
void	*safe_calloc(size_t n, t_shell *ms);
char	*safe_substr(char *stt, char *end, t_shell *ms);

#endif
