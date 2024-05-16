/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 18:29:11 by jmertane          #+#    #+#             */
/*   Updated: 2024/05/16 17:12:51 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	increment_shell_level(t_shell *ms)
{
	int		shlvl;
	char	*content;
	char	*envp;

	content = envp_exists("SHLVL", ms);
	if (content == NULL)
		envp_add(ms, "SHLVL=1");
	else if (ft_atoi(content) < 0)
		envp_update(ms, "SHLVL=0");
	else if (ft_atoi(content) > 999)
	{
		error_logger("warning: ", "", "shlvl too high, resetting to 1", ms);
		envp_update(ms, "SHLVL=1");
	}
	else if (ft_atoi(content) == 999)
		envp_remove(ms, "SHLVL");
	else
	{
		shlvl = ft_atoi(content) + 1;
		content = safe_trash(ft_itoa(shlvl), ALLOCATED, ms);
		envp = safe_trash(ft_strjoin("SHLVL=", content), ALLOCATED, ms);
		envp_update(ms, envp);
	}
}

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
	increment_shell_level(ms);
	ms->cwd = ft_strdup(envp_exists("PWD", ms));
	ms->pipefd[RD_END] = -1;
	ms->pipefd[WR_END] = -1;
	ms->tempfd = -1;
	ms->excode = SUCCESS;
}
