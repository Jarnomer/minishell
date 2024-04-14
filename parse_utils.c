/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 19:36:06 by jmertane          #+#    #+#             */
/*   Updated: 2024/04/14 15:50:50 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_parser	*parser_last(t_parser *file)
{
	if (!file)
		return (NULL);
	while (file->next)
		file = file->next;
	return (file);
}

int	parser_length(t_parser *file)
{
	int	len;

	if (!file)
		return (0);
	len = 0;
	while (file)
	{
		file = file->next;
		len++;
	}
	return (len);
}

void	parser_append(t_parser **lst, t_parser *new)
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
	if (!*argv)
		return (NULL);
	temp = find_breakpoint(argv, c);
	new = safe_calloc(sizeof(t_parser), ms);
	safe_substr(&new->content, argv, temp, ms);
	if (ft_strchr(new->content, c))
		filter_quotes(new->content, c, ms);
	parser_append(lst, new);
	return (temp);
}
