/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_argv.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 16:56:34 by jmertane          #+#    #+#             */
/*   Updated: 2024/04/17 16:56:36 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	assing_mode(t_module *mod, int mode)
{
	t_parser	*temp;

	if (mode == -1)
		temp = mod->command;
	else if (mode == OUTFILE || mode == APPEND)
		temp = mod->outfiles;
	else
		temp = mod->infiles;
	while (temp->next)
		temp = temp->next;
	temp->mode = mode;
}

static char	*append_file(char *input, int *mode)
{
	if (*(input + 1) == OUTDIRECT)
		*mode = APPEND;
	else if (*(input + 1) == INDIRECT)
		*mode = HEREDOC;
	else if (*input == OUTDIRECT)
		*mode = OUTFILE;
	else if (*input == INDIRECT)
		*mode = INFILE;
	if (*mode == APPEND || *mode == HEREDOC)
		input += 2;
	else
		input += 1;
	return (input);
}

static char	*find_endpoint(char *argv, char delim, int mode)
{
	if (mode == HEREDOC)
		return (find_breakpoint(argv, delim, EMPTY));
	else if (*(argv + 1) != QUESTIONMARK)
		return (find_breakpoint(argv, delim, DOLLAR));
	else
		return (argv + 2);
}

static char	*append_argv(char *argv, t_parser **lst, int mode, t_shell *ms)
{
	t_parser	*new;
	char		*end;
	char		delim;

	delim = assign_delimiter(argv);
	end = find_endpoint(argv, delim, mode);
	new = safe_calloc(sizeof(t_parser), ms);
	parser_append(lst, new);
	safe_substr(&new->content, argv, end, ms);
	if (ft_strchr(new->content, delim))
		filter_quotes(new->content, delim, ms);
	if (ft_strchr(new->content, DOLLAR) && mode != HEREDOC)
		parse_envp(new, mode, ms);
	return (end);
}

char	*parse_argv(char *input, t_module *mod, t_shell *ms)
{
	int		mode;

	mode = -1;
	if (ft_isredirect(*input))
		input = append_file(input, &mode);
	if (mode == -1)
		input = append_argv(input, &mod->command, mode, ms);
	else if (mode == OUTFILE || mode == APPEND)
		input = append_argv(input, &mod->outfiles, mode, ms);
	else if (mode == INFILE || mode == HEREDOC)
		input = append_argv(input, &mod->infiles, mode, ms);
	assing_mode(mod, mode);
	return (input);
}
