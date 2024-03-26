/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkinaret <vkinaret@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 16:05:16 by vkinaret          #+#    #+#             */
/*   Updated: 2023/11/07 19:28:31 by vkinaret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	min_value(const char *str, int i, int sign)
{
	long	nbr;

	nbr = 0;
	if (sign == -1)
	{
		while (str[i] >= '0' && str[i] <= '9')
		{
			if (nbr < -2147483648 / 10)
				return (1);
			nbr = nbr * 10;
			if (nbr < -2147483648 + (str[i] - '0'))
				return (1);
			nbr = nbr - (str[i] - '0');
			i++;
		}
	}
	return (0);
}

static int	max_value(const char *str, int i, int sign)
{
	long	nbr;

	nbr = 0;
	if (sign == 1)
	{
		while (str[i] >= '0' && str[i] <= '9')
		{
			if (nbr > 2147483647 / 10)
				return (0);
			nbr = nbr * 10;
			if (nbr > 2147483647 - (str[i] - '0'))
				return (0);
			nbr = nbr + (str[i] - '0');
			i++;
		}
	}
	return (1);
}

static int	return_value(const char *str, int i)
{
	int		rv;
	long	nbr;

	nbr = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		nbr = nbr * 10;
		nbr = nbr + (str[i] - '0');
		i++;
	}
	rv = (int)nbr;
	return (nbr);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	sign;

	i = 0;
	sign = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == 43 || str[i] == 45)
	{
		if (str[i] == 45)
			sign = -1;
		i++;
	}
	if (min_value(str, i, sign) == 1)
		return (0);
	if (max_value(str, i, sign) == 0)
		return (-1);
	return (return_value(str, i) * sign);
}
