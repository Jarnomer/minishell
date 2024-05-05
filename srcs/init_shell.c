/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 18:29:11 by jmertane          #+#    #+#             */
/*   Updated: 2024/05/04 12:00:16 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	create_prompt(t_shell *ms)
{
	safe_strdup(&ms->prompt, "", ms);
	safe_strjoin(&ms->prompt, V, "mini", ms);
	safe_strjoin(&ms->prompt, ms->prompt, T, ms);
	safe_strjoin(&ms->prompt, ms->prompt, G, ms);
	safe_strjoin(&ms->prompt, ms->prompt, "$ ", ms);
	safe_strjoin(&ms->prompt, ms->prompt, T, ms);
}

static void	init_envp(t_shell *ms)
{
	extern char	**environ;
	int			i;

	while (environ[ms->envp_size] != NULL)
		ms->envp_size++;
	ms->envp = safe_calloc((ms->envp_size + 1) * sizeof(char *), ms);
	i = 0;
	while (i < ms->envp_size)
	{
		safe_strdup(&ms->envp[i], environ[i], ms);
		i++;
	}
}

void	init_shell(t_shell *ms)
{
	ft_bzero(ms, sizeof(*ms));
	create_prompt(ms);
	init_envp(ms);
	ms->pipefd[RD_END] = -1;
	ms->pipefd[WR_END] = -1;
	ms->tempfd = -1;
	ms->excode = SUCCESS;
}
