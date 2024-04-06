/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_runtime.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 18:28:44 by jmertane          #+#    #+#             */
/*   Updated: 2024/04/06 14:56:20 by jmertane         ###   ########.fr       */
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
		if ((*lst)->infd != -1)
			close((*lst)->infd);
		if ((*lst)->outfd != -1)
			close((*lst)->outfd);
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
	if (ms->pipefd[RD_END] != -1)
		close(ms->pipefd[RD_END]);
	if (ms->pipefd[WR_END] != -1)
		close(ms->pipefd[WR_END]);
	if (ms->tempfd != -1)
		close(ms->tempfd);
}
