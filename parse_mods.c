/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_inputs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 18:32:53 by jmertane          #+#    #+#             */
/*   Updated: 2024/04/25 20:06:04 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*build_argument(char *input, t_parser *new, t_shell *ms)
{
	char	*start;

	while (*input && ft_isspace(*input))
		input++;
	start = input;
	input = parse_input(input, new);
	safe_substr(&new->content, start, input, ms);
	parse_argv(new, ms);
	return (input);
}

static void	append_argument(t_parser *new, t_module *mod)
{
	if (new->mode == -1)
		parser_append(&mod->command, new);
	else if (new->mode == OUTFILE || new->mode == APPEND)
		parser_append(&mod->outfiles, new);
	else if (new->mode == INFILE || new->mode == HEREDOC)
		parser_append(&mod->infiles, new);
}

static char	*check_redirect(char *input, t_parser *new)
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
	if (new->mode == APPEND
		|| new->mode == HEREDOC)
		input += 2;
	else if (new->mode == INFILE
		|| new->mode == OUTFILE)
		input += 1;
	return (input);
}

void	parse_modules(t_module **lst, t_shell *ms)
{
	t_module	*mod;
	t_parser	*new;
	char		*input;

	mod = *lst;
	while (mod)
	{
		input = mod->input;
		while (*input)
		{
			while (ft_isspace(*input))
				input++;
			if (!*input)
				break ;
			new = safe_calloc(sizeof(t_parser), ms);
			input = check_redirect(input, new);
			append_argument(new, mod);
			input = build_argument(input, new, ms);
		}
		mod = mod->next;
	}
}
