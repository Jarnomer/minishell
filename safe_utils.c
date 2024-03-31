#include "minishell.h"

static void	error_occured(t_shell *ms)
{
	perror("Memory allocate failed!");
	self_destruct(ms);
	exit(ENOMEM);
}

char	*safe_substr(char *stt, char *end, t_shell *ms)
{
	void	*s;

	s = ft_substr(stt, 0, end - stt);
	if (!s)
		error_occured(ms);
	return (s);
}

void	*safe_calloc(size_t n, t_shell *ms)
{
	void	*p;

	p = ft_calloc(1, n);
	if (!p)
		error_occured(ms);
	return (p);
}
