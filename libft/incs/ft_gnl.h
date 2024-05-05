/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gnl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 18:22:10 by jmertane          #+#    #+#             */
/*   Updated: 2024/05/04 20:37:33 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_GNL_H
# define FT_GNL_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 100
# endif

# include "libft.h"

typedef struct s_gnl
{
	char			*content;
	struct s_gnl	*next;
}	t_gnl;

char	*get_next_line(int fd);
int		found_new_line(t_gnl *lst);
int		get_line_len(t_gnl *lst);
void	prep_next_iter(char *content);
void	append_list(t_gnl **lst, t_gnl *new, char *s);
char	*clean_list(t_gnl **lst, char *line);

#endif
