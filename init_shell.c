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

void	init_shell(t_shell *ms)
{
	ft_bzero(ms, sizeof(*ms));
	init_fds(&ms->fds);
	ms->envp = init_environ();
	ms->prompt = ft_strdup("minishell~>");
	if (!ms->prompt)
		perror("Malloc failed!");
}
