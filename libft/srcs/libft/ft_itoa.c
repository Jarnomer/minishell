/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 16:22:39 by jmertane          #+#    #+#             */
/*   Updated: 2024/05/05 14:18:37 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

static void	st_fll_str(char *str, int n, int len)
{
	if (n < 0)
	{
		*str = '-';
		n *= -1;
	}
	while (n != 0)
	{
		--len;
		*(str + len) = n % 10 + '0';
		n /= 10;
	}
}

static int	st_get_bff(int n)
{
	int	bff;

	bff = (n == 0) + (n < 0);
	while (n != 0)
	{
		n /= 10;
		++bff;
	}
	return (bff);
}

char	*ft_itoa(int n)
{
	char	*new;
	int		bff;

	if (n == 0)
		return (ft_strdup("0"));
	else if (n == INT_MIN)
		return (ft_strdup("-2147483648"));
	bff = st_get_bff(n);
	new = ft_calloc(bff + 1, sizeof(char));
	if (new)
		st_fll_str(new, n, bff);
	return (new);
}
