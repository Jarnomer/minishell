/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_files.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 18:23:27 by jmertane          #+#    #+#             */
/*   Updated: 2024/05/01 18:23:30 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*prep_next_redirect(char *input)
{
	input++;
	if (ft_isredirect(*input))
		input++;
	while (ft_isspace(*input))
		input++;
	return (input);
}

static int	handle_outfile(t_parser *outfile, t_module *mod, t_shell *ms)
{
	outfile = open_outfile(outfile, mod, ms);
	if (!outfile)
		return (FAILURE);
	return (SUCCESS);
}

static int	handle_indirect(t_parser *infile, t_module *mod, t_shell *ms)
{
	infile = open_infile(infile, mod, ms);
	if (!infile)
		return (FAILURE);
	return (SUCCESS);
}

static char	*find_redirect(char *input)
{
	while (*input)
	{
		if (*input == '$' || (!ft_ismeta(*input)
				&& *input != INDIRECT && *input != OUTDIRECT))
			input++;
		else if (ft_ismeta(*input))
		{
			input++;
			while (*input && *input != '\'' && *input != '\"')
				input++;
			input++;
		}
		else
			return (input);
	}
	return (input);
}

int	parse_files(t_module *mod, t_shell *ms)
{
	static t_parser	*infile;
	static t_parser	*outfile;
	char			*input;

	input = mod->input;
	infile = mod->infiles;
	outfile = mod->outfiles;
	while (*input)
	{
		input = find_redirect(input);
		if (!*input)
			break ;
		if (*input == INDIRECT
			&& handle_indirect(infile, mod, ms) == FAILURE)
			return (FAILURE);
		else if (*input == OUTDIRECT
			&& handle_outfile(outfile, mod, ms) == FAILURE)
			return (FAILURE);
		input = prep_next_redirect(input);
	}
	return (SUCCESS);
}
