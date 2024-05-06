/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 16:34:39 by jmertane          #+#    #+#             */
/*   Updated: 2024/05/05 14:19:35 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

int	ft_putendl_fd(char *s, int fd)
{
	int	ln;

	ln = ft_strlen(s) + 1;
	if (ft_putstr_fd(s, fd) == -1)
		return (-1);
	if (ft_putchar_fd('\n', fd) == -1)
		return (-1);
	return (ln);
}
