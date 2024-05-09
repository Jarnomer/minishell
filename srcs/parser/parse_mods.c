/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_mods.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 18:32:53 by jmertane          #+#    #+#             */
/*   Updated: 2024/05/09 17:44:52 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static char	*build_argument(char *s, t_parser *new, t_module *mod, t_shell *ms)
{
	char	*start;

	while (*s && ft_isspace(*s))
		s++;
	start = s;
	s = parse_input(s, new);
	safe_substr(&new->content, start, s, ms);
	parse_argv(new, mod, ms);
	return (s);
}

static void	append_argument(t_parser *new, t_parser *prev, t_module *mod)
{
	if (prev != NULL && prev->joinable == true)
	{
		new->mode = prev->mode;
		parser_append(&prev, new);
	}
	else if (new->mode == -1)
		parser_append(&mod->command, new);
	else if (new->mode == OUTFILE || new->mode == APPEND)
		parser_append(&mod->outfiles, new);
	else if (new->mode == INFILE || new->mode == HEREDOC)
		parser_append(&mod->infiles, new);
}

static char	*check_redirect(char *input, t_parser *new)
{
	if (ft_isredirect(*input))
	{
		if (*(input + 1) == OUTDIRECT)
			new->mode = APPEND;
		else if (*(input + 1) == INDIRECT)
			new->mode = HEREDOC;
		else if (*input == OUTDIRECT)
			new->mode = OUTFILE;
		else if (*input == INDIRECT)
			new->mode = INFILE;
	}
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

static void	parse_mod(char *input, t_module *mod, t_shell *ms)
{
	t_parser	*new;
	t_parser	*prev;

	prev = NULL;
	while (*input)
	{
		while (ft_isspace(*input))
			input++;
		if (!*input)
			break ;
		new = safe_calloc(sizeof(t_parser), ms);
		input = check_redirect(input, new);
		append_argument(new, prev, mod);
		input = build_argument(input, new, mod, ms);
		prev = new;
	}
}

void	parse_modules(t_module **lst, t_shell *ms)
{
	t_module	*mod;
	char		*input;

	mod = *lst;
	while (mod)
	{
		input = mod->input;
		parse_mod(input, mod, ms);
		parse_expands(mod, ms);
		mod = mod->next;
	}
}
