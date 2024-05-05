/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 15:51:00 by jmertane          #+#    #+#             */
/*   Updated: 2024/05/05 14:20:26 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	*ft_strdup(const char *s1)
{
	char	*new;
	int		ln;

	ln = ft_strlen(s1) + 1;
	new = ft_calloc(ln, sizeof(char));
	if (new)
		ft_strlcpy(new, s1, ln);
	return (new);
}
