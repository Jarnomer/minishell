/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 19:36:06 by jmertane          #+#    #+#             */
/*   Updated: 2024/04/05 19:36:08 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	append_parser(t_parser **lst, t_parser *new)
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

char	*parse_argument(char *argv, char c, t_parser **lst, t_shell *ms)
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
	append_parser(lst, new);
	return (temp);
}
