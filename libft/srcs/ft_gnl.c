/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gnl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 18:22:14 by jmertane          #+#    #+#             */
/*   Updated: 2024/05/04 20:39:03 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

static char	*build_new_line(t_gnl *lst)
{
	char	*line;
	int		ln;
	int		i;

	ln = get_line_len(lst);
	line = malloc(sizeof(char) * (ln + 1));
	if (!line || !lst)
		return (free(line), NULL);
	while (lst)
	{
		i = -1;
		while (lst->content[++i] && lst->content[i] != '\n')
			line[i] = lst->content[i];
		if (lst->content[i] == '\n')
			line[i++] = '\n';
		line[i] = '\0';
		if (!lst->next)
			prep_next_iter(lst->content);
		lst = lst->next;
		line += i;
	}
	return (line - ln);
}

static int	init_new_iter(t_gnl **lst, int fd)
{
	t_gnl	*new;
	char	*bff;
	int		bts;

	new = *lst;
	while (!found_new_line(new))
	{
		new = malloc(sizeof(t_gnl));
		bff = malloc(sizeof(char) * (BUFFER_SIZE + 1));
		bts = read(fd, bff, BUFFER_SIZE);
		if (!bff || !new || bts < 0)
			return (free(bff), free(new), 0);
		else if (!bts)
			return (free(bff), free(new), 1);
		bff[bts] = '\0';
		append_list(lst, new, bff);
	}
	return (1);
}

char	*get_next_line(int fd)
{
	static t_gnl	*lst = NULL;
	char			*line;

	if (BUFFER_SIZE <= 0 || fd < 0
		|| !init_new_iter(&lst, fd))
		return (clean_list(&lst, NULL));
	line = build_new_line(lst);
	return (clean_list(&lst, line));
}
