/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_runtime.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 18:28:44 by jmertane          #+#    #+#             */
/*   Updated: 2024/05/05 15:53:36 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	free_parser(t_parser **lst)
{
	t_parser	*temp;

	while (*lst)
	{
		temp = (*lst)->next;
		parser_delone(*lst);
		*lst = temp;
	}
	*lst = NULL;
}

static void	free_modules(t_module **lst)
{
	t_module	*temp;

	while (*lst)
	{
		temp = (*lst)->next;
		if ((*lst)->cmd != NULL)
			free((*lst)->cmd);
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
	if (ms->trash != NULL)
		free_parser(&ms->trash);
	ms->index = 0;
}
