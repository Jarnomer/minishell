/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 13:36:58 by vkinaret          #+#    #+#             */
/*   Updated: 2024/05/05 15:52:49 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	builtin_env(t_shell *ms, int i, int j)
{
	while (ms->envp[i] != NULL)
	{
		j = 0;
		while (ms->envp[i][j] != '=' && ms->envp[i][j] != '\0')
			j++;
		if (ms->envp[i][j] == '=')
			ft_putendl_fd(ms->envp[i], 1);
		i++;
	}
	ms->exitcode = 0;
}
