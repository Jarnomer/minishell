/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 18:32:50 by jmertane          #+#    #+#             */
/*   Updated: 2024/04/04 18:33:02 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*format_command(char *argv, char c, t_module *mod, t_shell *ms)
{
	t_parser	*new;
	char		*temp;

	while (ft_isspace(*argv))
		argv++;
	temp = find_breakpoint(argv, c);
	new = safe_calloc(sizeof(t_parser), ms);
	safe_substr(&new->content, argv, temp, ms);
	if (ft_strchr(new->content, c))
		filter_quotes(new->content, c, ms);
	append_parser(&mod->command, new);
	return (temp);
}

char	*handle_command(char *input, t_module *mod, t_shell *ms)
{
	char	c;

	c = assign_delimiter(input);
	return (format_command(input, c, mod, ms));
}
