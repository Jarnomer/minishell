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

void	free_envp(t_shell *ms)
{
	int i;

	i = 0;
	while (i < ms->envp_size)
	{
		free(ms->envp[i]);
		i++;
	}
	free(ms->envp);
}

void	free_struct(t_shell *ms)
{
	int i;

	i = 0;
	if (ms->prompt)
		free(ms->prompt);
	if (ms->input)
		free(ms->input);
	free_envp(ms);
}
