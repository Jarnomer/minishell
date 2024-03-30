#include "minishell.h"

static void	init_fds(t_descriptors **fds)
{
	if (!fds || !*fds)
		return ;
	(*fds)->pipe[WR_END] = -1;
	(*fds)->pipe[RD_END] = -1;
	(*fds)->in = -1;
	(*fds)->out = -1;
}

void	init_minishell(t_shell *ms)
{
	extern char **environ;

	ft_bzero(ms, sizeof(*ms));
	init_fds(&ms->fds);
	ms->envp = environ;
	ms->prompt = ft_strdup("minishell~>");
}
