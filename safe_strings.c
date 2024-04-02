#include "minishell.h"

void	safe_strtrim(char **src, char *set, t_shell *ms)
{
	char	*s;

	if (!src || !*src || !set)
		return ;
	s = ft_strtrim(*src, set);
	if (!s)
		safe_fn_error(ms);
	if (src != NULL)
		free(*src);
	*src = s;
}

void	safe_strjoin(char **dst, char *s1, char *s2, t_shell *ms)
{
	char	*s;

	if (!dst || !s1 || !s2)
		return ;
	s = ft_strjoin(s1, s2);
	if (!s)
		safe_fn_error(ms);
	if (dst != NULL)
		free(*dst);
	*dst = s;
}

void	safe_strdup(char **dst, char *src, t_shell *ms)
{
	char	*s;

	if (!dst || !src || !*src)
		return ;
	s = ft_strdup(src);
	if (!s)
		safe_fn_error(ms);
	if (dst != NULL)
		free(*dst);
	*dst = s;
}

void	safe_substr(char **dst, char *stt, char *end, t_shell *ms)
{
	char	*s;

	if (!dst || stt >= end)
		return ;
	s = ft_substr(stt, 0, end - stt);
	if (!s)
		safe_fn_error(ms);
	if (dst != NULL)
		free(*dst);
	*dst = s;
}
