/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 15:49:23 by jmertane          #+#    #+#             */
/*   Updated: 2024/05/05 14:18:13 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void	*ft_calloc(size_t count, size_t size)
{
	void	*new;

	if (count != 0 && size > SIZE_MAX / count)
		return (NULL);
	new = malloc(count * size);
	if (new)
		ft_bzero(new, count * size);
	return (new);
}
