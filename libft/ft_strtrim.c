/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 16:12:55 by jmertane          #+#    #+#             */
/*   Updated: 2023/11/16 16:22:33 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	int		stt;
	int		end;

	if (!s1 || !set)
		return (NULL);
	stt = 0;
	while (s1[stt] && ft_strchr(set, s1[stt]))
		++stt;
	end = ft_strlen(s1);
	while (end > stt && ft_strchr(set, s1[end]))
		--end;
	return (ft_substr(s1, stt, end - stt + 1));
}
