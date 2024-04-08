/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 16:17:03 by jmertane          #+#    #+#             */
/*   Updated: 2023/11/26 13:10:45 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**st_mem_cln(char **arr, int wrd)
{
	while (--wrd >= 0)
		free(arr[wrd]);
	free(arr);
	return (NULL);
}

static char	**st_fll_arr(char **arr, char const *s, char c, int cnt)
{
	int	stt;
	int	end;
	int	wrd;

	wrd = 0;
	end = 0;
	while (wrd < cnt)
	{
		while (s[end] == c)
			++end;
		stt = end;
		while (s[end] && s[end] != c)
			++end;
		arr[wrd] = ft_substr(s, stt, end - stt);
		if (!arr[wrd])
			return (st_mem_cln(arr, wrd));
		++end;
		++wrd;
	}
	arr[cnt] = NULL;
	return (arr);
}

static int	st_wrd_cnt(char const *s, char c)
{
	int	cnt;

	cnt = 0;
	while (*s)
	{
		while (*s == c)
			++s;
		if (*s)
			++cnt;
		while (*s && *s != c)
			++s;
	}
	return (cnt);
}

char	**ft_split(char const *s, char c)
{
	char	**arr;
	int		cnt;

	if (!s)
		return (NULL);
	cnt = st_wrd_cnt(s, c);
	arr = malloc(sizeof(char *) * (cnt + 1));
	if (!arr)
		return (NULL);
	return (st_fll_arr(arr, s, c, cnt));
}
