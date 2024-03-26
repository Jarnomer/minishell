/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkinaret <vkinaret@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 11:32:11 by vkinaret          #+#    #+#             */
/*   Updated: 2023/11/05 13:42:38 by vkinaret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check_size(char const *s1, char const *s2)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s1[i] != '\0')
		i++;
	while (s2[j] != '\0')
		j++;
	return (i + j);
}

static char	*string_one_is_null(char const *s2, int len)
{
	int		i;
	char	*str;

	i = 0;
	str = malloc(len + 1);
	if (str == NULL)
		return (NULL);
	while (s2[i] != '\0')
	{
		str[i] = s2[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

static char	*string_two_is_null(char const *s1, int len)
{
	int		i;
	char	*str;

	i = 0;
	str = malloc(len + 1);
	if (str == NULL)
		return (NULL);
	while (s1[i] != '\0')
	{
		str[i] = s1[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = 0;
	if (s1[i] == '\0' && s2[i] != '\0')
		return (string_one_is_null(s2, check_size(s1, s2)));
	if (s2[i] == '\0' && s1[i] != '\0')
		return (string_two_is_null(s1, check_size(s1, s2)));
	str = malloc(check_size(s1, s2) + 1);
	if (str == NULL)
		return (NULL);
	while (s1[i] != '\0')
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0')
	{
		str[i + j] = s2[j];
		j++;
	}
	str[i + j] = '\0';
	return (str);
}
