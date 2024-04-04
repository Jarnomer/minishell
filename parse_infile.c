/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_infile.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 18:32:52 by jmertane          #+#    #+#             */
/*   Updated: 2024/04/04 18:33:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	append_infile(t_parser **lst, t_parser *new)
{
	t_parser	*temp;

	if (!*lst)
		*lst = new;
	else
	{
		temp = *lst;
		while (temp->next)
			temp = temp->next;
		temp->next = new;
	}
}

static char	*format_infile(char *argv, char c, t_module *mod, t_shell *ms)
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
	append_infile(&mod->infiles, new);
	return (temp);
}

char	*handle_infile(char *input, int *mode, t_module *mod, t_shell *ms)
{
	char	c;

	if (*(input + 1) == '<')
	{
		input += 2;
		*mode = HEREDOC;
	}
	else
	{
		input += 1;
		*mode = INFILE;
	}
	c = assign_delimiter(input);
	return (format_infile(input, c, mod, ms));
}
