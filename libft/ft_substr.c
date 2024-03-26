/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkinaret <vkinaret@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 11:31:34 by vkinaret          #+#    #+#             */
/*   Updated: 2023/11/07 19:58:30 by vkinaret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check_size(char const *s, unsigned int start, size_t len)
{
	int	size;

	size = (int)len;
	if (len > (size_t)ft_strlen(s + start))
		size = ft_strlen(s + start);
	return (size);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t		i;
	char		*substr;

	i = 0;
	if (s == NULL)
		return (NULL);
	if ((size_t)start >= ft_strlen(s))
	{
		substr = malloc(1);
		if (substr == NULL)
			return (NULL);
		substr[0] = '\0';
		return (substr);
	}
	substr = malloc(check_size(s, start, len) + 1);
	if (substr == NULL)
		return (NULL);
	while (i < len && s[start] != '\0')
	{
		substr[i] = s[start];
		i++;
		start++;
	}
	substr[i] = '\0';
	return (substr);
}
