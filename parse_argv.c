/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_argv.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 16:56:34 by jmertane          #+#    #+#             */
/*   Updated: 2024/04/21 19:24:08 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	check_joining(char *start, t_parser *new, t_shell *ms)
{
	char	delim;
	char	*end;

	if (!new->prev)
		return ;
	end = start;
	delim = assign_delimiter(start);
	if (delim == EMPTY)
		delim = DOLLAR;
	ft_printf("debug print: delim = %c | start = %c | end = %c\n", delim, *start, *end);
	while (*end && *end != delim && !ft_isredirect(*end))
		end++;
	while (*start && *start != delim && !ft_isredirect(*start)
		&& !ft_isspace(*start))
		start++;
	printf("debug print: start = %c | end = %c\n", *start, *end);
	if (!*start && !*end)
		return ;
	if (start == end && !ft_isredirect(*start))
	{
		ft_printf("JOINING ARGUMENTS!\n");
		return ;
		parser_join(new->prev, new, ms);
	}
}

static char	*check_redirection(char *input, t_parser *new)
{
	if (*(input + 1) == OUTDIRECT)
		new->mode = APPEND;
	else if (*(input + 1) == INDIRECT)
		new->mode = HEREDOC;
	else if (*input == OUTDIRECT)
		new->mode = OUTFILE;
	else if (*input == INDIRECT)
		new->mode = INFILE;
	else
		new->mode = -1;
	if (new->mode == APPEND || new->mode == HEREDOC)
		input += 2;
	else if (new->mode == INFILE || new->mode == OUTFILE)
		input += 1;
	return (input);
}

static char	*find_endpoint(char *argv, char delim, int mode)
{
	if (mode == HEREDOC)
		return (find_breakpoint(argv, delim, '\0'));
	else if (*argv == DOLLAR && *(argv + 1) == QUESTIONMARK)
		return (argv + 2);
	else
		return (find_breakpoint(argv, delim, DOLLAR));
}

static char	*append_argv(char *argv, \
	t_parser **lst, t_parser *new, t_shell *ms)
{
	char		*end;
	char		delim;
	bool		checker;

	checker = true;
	parser_append(lst, new);
	delim = assign_delimiter(argv);
	end = find_endpoint(argv, delim, new->mode);
	safe_substr(&new->content, argv, end, ms);
	if (ft_strchr(new->content, delim))
		filter_quotes(new->content, delim, &checker, ms);
	if (checker == true && new->mode != HEREDOC
		&& ft_strchr(new->content, DOLLAR))
		parse_envp(new, new->mode, ms);
	return (end);
}

char	*parse_argv(char *input, t_module *mod, t_shell *ms)
{
	t_parser	*new;
	char		*start;

	new = safe_calloc(sizeof(t_parser), ms);
	input = check_redirection(input, new);
	while (ft_isspace(*input))
		input++;
	start = input;
	if (new->mode == -1)
		input = append_argv(input, &mod->command, new, ms);
	else if (new->mode == OUTFILE || new->mode == APPEND)
		input = append_argv(input, &mod->outfiles, new, ms);
	else if (new->mode == INFILE || new->mode == HEREDOC)
		input = append_argv(input, &mod->infiles, new, ms);
	check_joining(start, new, ms);
	return (input);
}
