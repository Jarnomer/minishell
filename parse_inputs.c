/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_inputs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 18:32:53 by jmertane          #+#    #+#             */
/*   Updated: 2024/04/04 19:21:04 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*append_command(char *argv, t_module *mod, t_shell *ms)
{
	argv = handle_command(argv, mod, ms);
	return (argv);
}

static char	*append_outfile(char *argv, t_module *mod, t_shell *ms)
{
	int		mode;

	argv = handle_outfile(argv, &mode, mod, ms);
	open_file(&mod->outfiles, mode);
	return (argv);
}

static char	*append_infile(char *argv, t_module *mod, t_shell *ms)
{
	int		mode;

	argv = handle_infile(argv, &mode, mod, ms);
	open_file(&mod->infiles, mode);
	return (argv);
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
			if (*input == '<')
				input = append_infile(input, mod, ms);
			else if (*input == '>')
				input = append_outfile(input, mod, ms);
			else
				input = append_command(input, mod, ms);
		}
		mod = mod->next;
	}
}
