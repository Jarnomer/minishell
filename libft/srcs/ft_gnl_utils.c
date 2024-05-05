/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gnl_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 18:22:26 by jmertane          #+#    #+#             */
/*   Updated: 2024/05/05 14:18:16 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

int	found_new_line(t_gnl *lst)
{
	int	i;

	if (!lst)
		return (0);
	i = -1;
	while (lst->content[++i])
		if (lst->content[i] == '\n')
			return (1);
	return (0);
}

int	get_line_len(t_gnl *lst)
{
	int		ln;
	int		i;

	if (!lst)
		return (0);
	ln = 0;
	while (lst)
	{
		i = 0;
		while (lst->content[i] && lst->content[i] != '\n')
			++i;
		ln += i;
		if (lst->content[i] == '\n')
			return (++ln);
		lst = lst->next;
	}
	return (ln);
}

void	prep_next_iter(char *content)
{
	char	*tmp;
	int		i;

	if (!content)
		return ;
	tmp = content;
	while (*tmp != '\n' && *tmp)
		++tmp;
	if (*tmp == '\n')
		++tmp;
	i = -1;
	while (tmp[++i])
		content[i] = tmp[i];
	content[i] = '\0';
}

void	append_list(t_gnl **lst, t_gnl *new, char *s)
{
	t_gnl	*tmp;

	if (!lst || !new || !s)
		return ;
	new->content = s;
	new->next = NULL;
	if (!*lst)
		*lst = new;
	else
	{
		tmp = *lst;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

char	*clean_list(t_gnl **lst, char *line)
{
	t_gnl	*tmp;

	if (!lst || !*lst)
		return (NULL);
	while ((*lst)->next)
	{
		tmp = (*lst)->next;
		free((*lst)->content);
		free(*lst);
		*lst = tmp;
	}
	if (line && *line)
		return (line);
	free((*lst)->content);
	free(*lst);
	free(line);
	*lst = NULL;
	return (NULL);
}
