/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_wc_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jankku <jankku@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 00:00:00 by jankku            #+#    #+#             */
/*   Updated: 2025/01/01 00:00:00 by jankku           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <expand.h>

static t_vec	sort_matches(t_vec *matches)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (i < matches->len)
	{
		j = i + 1;
		while (j < matches->len)
		{
			if (ft_strcmp(matches->data[i], matches->data[j]) > 0)
				vec_swap(matches, i, j);
			j++;
		}
		i++;
	}
	return (*matches);
}

/*
** Recursive pattern matching for wildcard *
** * matches any sequence (including empty)
*/
static int	match_pattern(const char *pattern, const char *str)
{
	if (*pattern == '\0')
		return (*str == '\0');
	if (*pattern == '*')
	{
		while (*(pattern + 1) == '*')
			pattern++;
		if (match_pattern(pattern + 1, str))
			return (1);
		while (*str)
		{
			if (match_pattern(pattern + 1, str + 1))
				return (1);
			str++;
		}
		return (0);
	}
	if (*pattern == *str)
		return (match_pattern(pattern + 1, str + 1));
	return (0);
}

static void	collect_matches(DIR *dir, char *pattern, t_vec *matches)
{
	struct dirent	*entry;

	entry = readdir(dir);
	while (entry)
	{
		if (entry->d_name[0] == '.' && pattern[0] != '.')
		{
			entry = readdir(dir);
			continue ;
		}
		if (match_pattern(pattern, entry->d_name))
			vec_push(matches, safe_strdup(entry->d_name));
		entry = readdir(dir);
	}
}

/*
** Get all files in current directory matching pattern
** Hidden files (starting with .) only match if pattern starts with .
*/
t_vec	get_matching_files(const char *pattern)
{
	DIR		*dir;
	t_vec	matches;
	char	*clean_pattern;

	matches = vec_new(0);
	clean_pattern = strip_quotes((char *)pattern);
	dir = opendir(".");
	if (!dir)
	{
		free(clean_pattern);
		return (matches);
	}
	collect_matches(dir, clean_pattern, &matches);
	closedir(dir);
	free(clean_pattern);
	return (sort_matches(&matches));
}
