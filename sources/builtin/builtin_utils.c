/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jankku <jankku@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 00:00:00 by jankku            #+#    #+#             */
/*   Updated: 2025/01/01 00:00:00 by jankku           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <builtin.h>

void	sort_str_arr(char **arr, size_t len)
{
	size_t	i;
	size_t	j;
	char	*temp;

	i = 0;
	while (i < len - 1)
	{
		j = i + 1;
		while (j < len)
		{
			if (ft_strcmp(arr[i], arr[j]) > 0)
			{
				temp = arr[i];
				arr[i] = arr[j];
				arr[j] = temp;
			}
			j++;
		}
		i++;
	}
}

bool	is_valid_identifier(const char *name, size_t len)
{
	size_t	i;

	if (len == 0)
		return (false);
	if (!ft_isalpha(name[0]) && name[0] != '_')
		return (false);
	i = 1;
	while (i < len)
	{
		if (!ft_isalnum(name[i]) && name[i] != '_')
			return (false);
		i++;
	}
	return (true);
}

bool	is_numeric(const char *str)
{
	size_t	i;

	if (!str || !str[0])
		return (false);
	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (!str[i])
		return (false);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (false);
		i++;
	}
	return (true);
}

bool	is_overflow(const char *str)
{
	unsigned long long	result;
	int					sign;
	size_t				i;

	result = 0;
	sign = 1;
	i = 0;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i])
	{
		if (result > ((unsigned long long)LLONG_MAX - (str[i] - '0')) / 10)
			return (true);
		result = result * 10 + (str[i] - '0');
		i++;
	}
	if (sign == -1 && result > (unsigned long long)LLONG_MAX + 1)
		return (true);
	return (false);
}
