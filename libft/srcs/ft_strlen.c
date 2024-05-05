/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 15:30:21 by jmertane          #+#    #+#             */
/*   Updated: 2024/05/05 14:20:37 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

size_t	ft_strlen(const char *s)
{
	size_t	ln;

	if (!s)
		return (0);
	ln = 0;
	while (s[ln])
		++ln;
	return (ln);
}
