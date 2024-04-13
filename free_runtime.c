/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_runtime.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 18:28:44 by jmertane          #+#    #+#             */
/*   Updated: 2024/04/13 14:55:12 by jmertane         ###   ########.fr       */
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

static void	reset_shell(t_shell *ms)
{
	ms->idx = 0;
}

void	free_runtime(t_shell *ms)
{
	if (!ms)
		return ;
	close_fds(ms);
	if (ms->input != NULL)
		free_single(&ms->input);
	if (ms->pids != NULL)
	{
		free(ms->pids);
		ms->pids = NULL;
	}
	if (ms->mods != NULL)
		free_modules(&ms->mods);
	reset_shell(ms);
}
