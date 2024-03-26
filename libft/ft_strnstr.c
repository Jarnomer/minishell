/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkinaret <vkinaret@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 16:03:24 by vkinaret          #+#    #+#             */
/*   Updated: 2023/11/05 13:52:39 by vkinaret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*helper_ft(char *str, char *sub, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	count;

	i = 0;
	count = 0;
	while (i < len && str[i] != '\0')
	{
		j = 0;
		while (str[i + j] == sub[j] && sub[j] != '\0' && (i + j) < len)
		{
			count++;
			j++;
		}
		if (count == ft_strlen(sub))
			return (&str[i]);
		else
			count = 0;
		i++;
	}
	return (NULL);
}

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	char	*str;
	char	*sub;

	str = (char *)haystack;
	sub = (char *)needle;
	if (sub[0] == '\0')
		return (&str[0]);
	return (helper_ft(str, sub, len));
}
