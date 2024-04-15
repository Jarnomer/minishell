/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_inputs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 18:32:53 by jmertane          #+#    #+#             */
/*   Updated: 2024/04/14 14:12:23 by jmertane         ###   ########.fr       */
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

static char	*append_argument(char *input, t_module *mod, t_shell *ms)
{
	int		mode;
	char	c;

	mode = -1;
	if (ft_issyntax(*input))
		input = append_file(input, &mode);
	c = assign_delimiter(input);
	if (mode == -1)
		input = parse_argument(input, c, &mod->command, ms);
	else if (mode == OUTFILE || mode == APPEND)
		input = parse_argument(input, c, &mod->outfiles, ms);
	else if (mode == INFILE || mode == HEREDOC)
		input = parse_argument(input, c, &mod->infiles, ms);
	if (input != NULL)
		assing_mode(mod, mode);
	return (input);
}

void	parse_inputs(t_module **lst, t_shell *ms)
{
	t_module	*mod;
	char		*input;

	mod = *lst;
	while (mod)
	{
		input = mod->input;
		while (*input)
		{
			while (ft_isspace(*input))
				input++;
			input = append_argument(input, mod, ms);
			if (!input)
				break ;
		}
		mod = mod->next;
	}
}
