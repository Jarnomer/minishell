#include "minishell.h"

static void	free_single(char **str)
{
	if (!str || !*str)
		return ;
	free(*str);
	*str = NULL;
}

static void	free_douple(char ***arr)
{
	int	i;

	if (!arr || !*arr)
		return ;
	i = 0;
	while ((*arr)[i])
	{
		free((*arr)[i]);
		(*arr)[i] = NULL;
		i++;
	}
	free(*arr);
	*arr = NULL;
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

void	self_destruct(t_shell *ms)
{
	if (!ms)
		return ;
	if (ms->input != NULL)
		free_single(&ms->input);
	if (ms->prompt != NULL)
		free_single(&ms->prompt);
	if (ms->mods != NULL)
		free_modules(&ms->mods);
	close_fds(&ms->fds);
}
