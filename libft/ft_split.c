/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkinaret <vkinaret@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 11:32:43 by vkinaret          #+#    #+#             */
/*   Updated: 2023/10/30 10:59:52 by vkinaret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	num_of_strings(char const *s, char c)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	if (s[i] != c && s[i] != '\0')
		count = 1;
	while (s[i] != '\0')
	{
		if (s[i] == c && s[i + 1] != c && s[i + 1] != '\0')
			count++;
		i++;
	}
	return (count);
}

static unsigned int	find_first_i(char const *s, char c, int i)
{
	int	j;
	int	count;

	j = 0;
	count = -1;
	if (s[j] != c)
		count = 0;
	if (s[j] != c && i == 0)
		return (0);
	while (s[j] != '\0')
	{
		if (s[j] == c && s[j + 1] != c && s[j + 1] != '\0')
			count++;
		if (count == i)
			return (j + 1);
		j++;
	}
	return (0);
}

static void	free_array(char **array, int i)
{
	while (i >= 0)
	{
		free(array[i]);
		i--;
	}
	free(array);
}

static char	*create_substr(char const *s, char c, int i)
{
	size_t			len;
	char			*substr;
	unsigned int	start;

	len = 0;
	start = find_first_i(s, c, i);
	while (s[start + len] != c && s[start + len] != '\0')
		len++;
	substr = ft_substr(s, start, len);
	return (substr);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	char	**array;

	i = 0;
	if (s == NULL)
		return (NULL);
	array = malloc((num_of_strings(s, c) + 1) * sizeof(char *));
	if (array == NULL)
		return (NULL);
	while (i < num_of_strings(s, c))
	{
		array[i] = create_substr(s, c, i);
		if (array[i] == NULL)
		{
			free_array(array, i);
			return (NULL);
		}
		i++;
	}
	array[i] = NULL;
	return (array);
}
