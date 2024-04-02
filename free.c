/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkinaret <vkinaret@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 13:08:50 by vkinaret          #+#    #+#             */
/*   Updated: 2024/03/30 13:08:51 by vkinaret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_fds(t_descriptors *fds)
{
	if (!fds)
		return ;
	if (fds->pipe[WR_END] != -1)
		close(fds->pipe[WR_END]);
	if (fds->pipe[RD_END] != -1)
		close(fds->pipe[RD_END]);
	if (fds->in != -1)
		close(fds->in);
	if (fds->out != -1)
		close(fds->out);
}

void	free_array(char **arr)
{
	int i;

	i = 0;
	if (!arr)
		return ;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void	free_parser(t_parser **lst)
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

void	free_modules(t_module **lst)
{
	t_module	*temp;

	if (!lst || !*lst)
		return ;
	while (*lst)
	{
		temp = (*lst)->next;
		if ((*lst)->input != NULL)
			free((*lst)->input);
		if ((*lst)->cmd != NULL)
			free_array((*lst)->cmd);
		if ((*lst)->parse != NULL)
			free_parser(&(*lst)->parse);
		*lst = temp;
	}
	free(*lst);
	*lst = NULL;
}

void	free_struct(t_shell *ms)
{
	if (ms->prompt)
		free(ms->prompt);
	if (ms->input)
		free(ms->input);
	if (ms->envp)
		free_array(ms->envp);
	if (ms->mods)
		free_modules(&ms->mods);
	close_fds(ms->fds);
}
