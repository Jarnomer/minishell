/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 16:04:54 by jmertane          #+#    #+#             */
/*   Updated: 2024/05/05 14:20:31 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*new;
	int		bff;

	if (!s1 || !s2)
		return (NULL);
	bff = ft_strlen(s1) + ft_strlen(s2) + 1;
	new = ft_calloc(bff, sizeof(char));
	if (!new)
		return (NULL);
	ft_strlcat(new, s1, bff);
	ft_strlcat(new, s2, bff);
	return (new);
}
