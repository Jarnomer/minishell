#include "minishell.h"

void	safe_fn_error(t_shell *ms)
{
	perror("Out of memory");
	free_runtime(ms, FAILURE);
	exit(ENOMEM);
}

void	*safe_calloc(size_t n, t_shell *ms)
{
	void	*p;

	p = ft_calloc(1, n);
	if (!p)
		safe_fn_error(ms);
	return (p);
}
