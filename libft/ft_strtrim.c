/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkinaret <vkinaret@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 11:32:51 by vkinaret          #+#    #+#             */
/*   Updated: 2023/10/30 11:08:27 by vkinaret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check_first(char const *s1, char const *set)
{
	int	i;
	int	j;
	int	flag;

	i = 0;
	while (s1[i] != '\0')
	{
		j = 0;
		flag = 0;
		while (set[j] != '\0')
		{
			if (s1[i] == set[j])
				flag = 1;
			j++;
		}
		if (flag == 1)
			i++;
		else
			break ;
	}
	return (i);
}

static int	check_last(const char *s1, const char *set)
{
	int	i;
	int	j;
	int	flag;

	i = 0;
	while (s1[i] != '\0')
		i++;
	while (i > 0)
	{
		j = 0;
		flag = 0;
		while (set[j] != '\0')
		{
			if (s1[i - 1] == set[j])
				flag = 1;
			j++;
		}
		if (flag == 1)
			i--;
		else
			break ;
	}
	return (i);
}

static char	*empty_str(char *str)
{
	str = malloc(1);
	if (str == NULL)
		return (NULL);
	str[0] = '\0';
	return (str);
}

char	*ft_strtrim(const char *s1, const char *set)
{
	int		i;
	int		len;
	char	*str;

	i = 0;
	if (s1 == NULL || set == NULL)
		return (NULL);
	if (check_last(s1, set) == 0)
	{
		str = 0;
		return (empty_str(str));
	}
	len = check_last(s1, set) - check_first(s1, set);
	str = malloc(len + 1);
	if (str == NULL)
		return (NULL);
	while (i < len)
	{
		str[i] = s1[check_first(s1, set) + i];
		i++;
	}
	str[i] = '\0';
	return (str);
}
