/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkinaret <vkinaret@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 16:02:29 by vkinaret          #+#    #+#             */
/*   Updated: 2023/11/05 13:43:26 by vkinaret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;
	int		flag;

	flag = 0;
	if (dstsize == 0)
		return (ft_strlen(src));
	i = ft_strlen(dst);
	if (dstsize > i)
		flag = 1;
	j = 0;
	while ((i + j) < (dstsize - 1) && src[j] != '\0')
	{
		dst[i + j] = src[j];
		j++;
	}
	dst[i + j] = '\0';
	if (i == 0)
		return (ft_strlen(src));
	if (flag == 1)
		return (i + ft_strlen(src));
	return (dstsize + ft_strlen(src));
}
