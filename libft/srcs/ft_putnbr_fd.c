/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 16:35:06 by jmertane          #+#    #+#             */
/*   Updated: 2024/05/05 14:19:38 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

static long	st_get_div(long n)
{
	long	div;
	int		i;

	i = 0;
	div = 1;
	if (n < 0)
		div *= -1;
	while (n != 0)
	{
		n /= 10;
		i++;
	}
	while (--i > 0)
		div *= 10;
	return (div);
}

int	ft_putnbr_fd(long n, int fd)
{
	long	div;
	int		len;

	len = 0;
	if (n < 0)
	{
		if (ft_putchar_fd('-', fd) == -1)
			return (-1);
		len++;
	}
	div = st_get_div(n);
	while (div != 0)
	{
		if (ft_putchar_fd(n / div + '0', fd) == -1)
			return (-1);
		n %= div;
		div /= 10;
		len++;
	}
	return (len);
}
