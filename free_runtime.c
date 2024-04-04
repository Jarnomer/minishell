/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_runtime.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 18:28:44 by jmertane          #+#    #+#             */
/*   Updated: 2024/04/04 18:28:45 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_parser(t_parser **lst)
{
	t_parser	*temp;

	if (!lst || !*lst)
		return ;
	while (*lst)
	{
		temp = (*lst)->next;
		if ((*lst)->fd != -1)
			close((*lst)->fd);
		free(*lst);
		*lst = temp;
	}
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
		if ((*lst)->command != NULL)
			free_parser(&(*lst)->command);
		if ((*lst)->infiles != NULL)
			free_parser(&(*lst)->infiles);
		if ((*lst)->outfiles != NULL)
			free_parser(&(*lst)->outfiles);
		free(*lst);
		*lst = temp;
	}
	*lst = NULL;
}

void	free_runtime(t_shell *ms, int errcode)
{
	if (!ms)
		return ;
	if (errcode == FAILURE
		&& ms->prompt != NULL)
		free_single(&ms->prompt);
	if (ms->input != NULL)
		free_single(&ms->input);
	if (ms->pids != NULL)
		free(ms->pids);
	if (ms->mods != NULL)
		free_modules(&ms->mods);
	if (ms->pipe[RD_END] != -1)
		close(ms->pipe[RD_END]);
	if (ms->pipe[WR_END] != -1)
		close(ms->pipe[WR_END]);
}
