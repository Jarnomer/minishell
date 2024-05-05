/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_allocs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 18:25:54 by jmertane          #+#    #+#             */
/*   Updated: 2024/05/05 15:54:20 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	**safe_double(t_parser *lst, t_shell *ms)
{
	char	**arr;
	int		len;
	int		i;

	if (!lst)
		return (NULL);
	len = parser_length(lst) + 1;
	arr = safe_calloc(len * sizeof(char *), ms);
	i = 0;
	while (lst)
	{
		arr[i] = lst->content;
		lst = lst->next;
		i++;
	}
	return (arr);
}

char	*safe_trash(char *str, int alloc_flag, t_shell *ms)
{
	t_parser	*new;

	if (!str)
		error_fatal(ENOMEM, MSG_MEM, ms);
	new = safe_calloc(sizeof(t_parser), ms);
	parser_append(&ms->trash, new);
	if (alloc_flag == ALLOCATED)
		new->content = str;
	else if (alloc_flag == ALLOCATE)
		safe_strdup(&new->content, str, ms);
	return (new->content);
}

void	*safe_calloc(size_t n, t_shell *ms)
{
	void	*p;

	p = ft_calloc(1, n);
	if (!p)
		error_fatal(ENOMEM, MSG_MEM, ms);
	return (p);
}
