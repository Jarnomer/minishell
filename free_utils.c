/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 18:26:05 by jmertane          #+#    #+#             */
/*   Updated: 2024/05/01 19:28:43 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_single(char **str)
{
	if (!str || !*str)
		return ;
	free(*str);
	*str = NULL;
}

void	free_double(char ***arr)
{
	int	i;

	if (!arr || !*arr)
		return ;
	i = 0;
	while ((*arr)[i])
		free_single(&(*arr)[i++]);
	free(*arr);
	*arr = NULL;
}

void	free_exit(t_shell *ms)
{
	if (!ms)
		return ;
	free_runtime(ms);
	if (ms->prompt != NULL)
		free_single(&ms->prompt);
	if (ms->envp != NULL)
		free_double(&ms->envp);
}
