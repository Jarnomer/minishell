#include "minishell.h"

static void	reset_fds(t_descriptors **fds)
{
	if (!fds || !*fds)
		return ;
	(*fds)->pipe[WR_END] = -1;
	(*fds)->pipe[RD_END] = -1;
	(*fds)->in = -1;
	(*fds)->out = -1;
}

static void	free_parser(t_parser **lst)
{
	t_parser	*temp;

	if (!lst || !*lst)
		return ;
	while (*lst)
	{
		temp = (*lst)->next;
		free(*lst);
		*lst = temp;
	}
	free(*lst);
	*lst = NULL;
}

static void	free_modules(t_module **lst)
{
	t_module	*temp;

	if (!lst || !*lst)
		return ;
	while (*lst)
	{
		temp = (*lst)->next;
		if ((*lst)->input != NULL)
			free_single(&(*lst)->input);
		if ((*lst)->cmd != NULL)
			free_douple(&(*lst)->cmd);
		if ((*lst)->parse != NULL)
			free_parser(&(*lst)->parse);
		*lst = temp;
	}
	free(*lst);
	*lst = NULL;
}

void	free_runtime(t_shell *ms)
{
	if (!ms)
		return ;
	if (ms->input != NULL)
		free_single(&ms->input);
	if (ms->mods != NULL)
		free_modules(&ms->mods);
	close_fds(&ms->fds);
	reset_fds(&ms->fds);
}
