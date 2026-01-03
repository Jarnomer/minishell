/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_str.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/01 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>

void	*safe_calloc(size_t size)
{
	void	*ptr;

	ptr = ft_calloc(1, size);
	if (!ptr)
	{
		perror(ERR_PROMPT);
		exit(EXIT_FAILURE);
	}
	return (ptr);
}

char	*safe_itoa(int num)
{
	char	*str;

	str = ft_itoa(num);
	if (!str)
	{
		perror(ERR_PROMPT);
		exit(EXIT_FAILURE);
	}
	return (str);
}

char	*safe_strdup(const char *s)
{
	char	*str;

	str = ft_strdup(s);
	if (!str)
	{
		perror(ERR_PROMPT);
		exit(EXIT_FAILURE);
	}
	return (str);
}

char	*safe_substr(const char *s, unsigned int start, size_t len)
{
	char	*str;

	str = ft_substr(s, start, len);
	if (!str)
	{
		perror(ERR_PROMPT);
		exit(EXIT_FAILURE);
	}
	return (str);
}

char	*safe_strjoin(const char *s1, const char *s2)
{
	char	*str;

	str = ft_strjoin(s1, s2);
	if (!str)
	{
		perror(ERR_PROMPT);
		exit(EXIT_FAILURE);
	}
	return (str);
}
