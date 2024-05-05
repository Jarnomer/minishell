/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 15:41:06 by jmertane          #+#    #+#             */
/*   Updated: 2024/05/05 14:20:24 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	*ft_strchr(char const *s, int c)
{
	if (!s)
		return (NULL);
	while (*s && *s != (char)c)
		++s;
	if (*s || !(char)c)
		return ((char *)s);
	return (NULL);
}
