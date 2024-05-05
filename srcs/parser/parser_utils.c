/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 19:36:06 by jmertane          #+#    #+#             */
/*   Updated: 2024/05/05 15:54:16 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_parser	*parser_last(t_parser *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

int	parser_length(t_parser *lst)
{
	if (!lst)
		return (0);
	else
		return (1 + parser_length(lst->next));
}

void	parser_delone(t_parser *lst)
{
	if (!lst)
		return ;
	if (lst->next != NULL)
		lst->next->prev = lst->prev;
	if (lst->prev != NULL)
		lst->prev->next = lst->next;
	free_single(&lst->content);
	free(lst);
	lst = NULL;
}

void	parser_append(t_parser **lst, t_parser *new)
{
	t_parser	*last;

	if (!lst || !new)
		return ;
	else if (!*lst)
		*lst = new;
	else
	{
		last = parser_last(*lst);
		last->next = new;
		new->prev = last;
	}
}
