/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_argv.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 16:56:34 by jmertane          #+#    #+#             */
/*   Updated: 2024/04/20 19:47:54 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	bool		expand_checker;

	expand_checker = true;
	parser_append(lst, new);
	delim = assign_delimiter(argv);
	end = find_endpoint(argv, delim, new->mode);
	safe_substr(&new->content, argv, end, ms);
	if (ft_strchr(new->content, delim))
		filter_quotes(new->content, delim, &expand_checker, ms);
	if (expand_checker == true && new->mode != HEREDOC
		&& ft_strchr(new->content, DOLLAR))
		parse_envp(new, new->mode, ms);
	return (end);
}

char	*parse_argv(char *input, t_module *mod, t_shell *ms)
{
	t_parser	*new;

	new = safe_calloc(sizeof(t_parser), ms);
	input = check_redirection(input, new);
	while (ft_isspace(*input))
		input++;
	if (new->mode == -1)
		input = append_argv(input, &mod->command, new, ms);
	else if (new->mode == OUTFILE || new->mode == APPEND)
		input = append_argv(input, &mod->outfiles, new, ms);
	else if (new->mode == INFILE || new->mode == HEREDOC)
		input = append_argv(input, &mod->infiles, new, ms);
	return (input);
}
