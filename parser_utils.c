/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 19:36:06 by jmertane          #+#    #+#             */
/*   Updated: 2024/04/25 20:43:28 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parser_join(t_parser *prev, t_parser *lst, t_shell *ms)
{
	t_parser	*temp;

	if (!prev || !lst)
		return ;
	safe_strjoin(&lst->content, prev->content, lst->content, ms);
	temp = prev;
	if (prev->prev == NULL)
		prev = prev->next;
	parser_delone(temp);
}

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
	int	len;

	if (!lst)
		return (0);
	len = 0;
	while (lst)
	{
		lst = lst->next;
		len++;
	}
	return (len);
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