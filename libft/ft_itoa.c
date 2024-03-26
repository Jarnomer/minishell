/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkinaret <vkinaret@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 11:33:24 by vkinaret          #+#    #+#             */
/*   Updated: 2023/10/30 10:50:48 by vkinaret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check_size(int n)
{
	int	count;

	if (n == -2147483648)
		return (11);
	count = 1;
	if (n < 0)
	{
		n = n * -1;
		count++;
	}
	while (n >= 10)
	{
		n = n / 10;
		count++;
	}
	return (count);
}

static char	*save_more_space(char *str, int size, int n, int i)
{
	int	t;
	int	count;

	while (size != 0)
	{
		t = n;
		count = 1;
		while (size != count)
		{
			t = t / 10;
			count++;
		}
		if (t >= 10)
			str[i] = t % 10 + '0';
		else
			str[i] = t + '0';
		size--;
		i++;
	}
	str[i] = '\0';
	return (str);
}

static char	*save_space(char *str, int size, int n)
{
	int	i;

	i = 0;
	if (n == -2147483648)
	{
		str[0] = '-';
		str[1] = '2';
		n = 147483648;
		size -= 2;
		i += 2;
	}
	if (n < 0)
	{
		str[0] = '-';
		n = n * -1;
		size--;
		i++;
	}
	str = save_more_space(str, size, n, i);
	return (str);
}

char	*ft_itoa(int n)
{
	int		size;
	char	*str;

	size = check_size(n);
	str = malloc(size + 1);
	if (str == NULL)
		return (NULL);
	str = save_space(str, size, n);
	return (str);
}
