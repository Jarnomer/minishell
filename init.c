/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkinaret <vkinaret@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 15:57:24 by vkinaret          #+#    #+#             */
/*   Updated: 2024/04/02 15:57:25 by vkinaret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static inline int	ft_isspace(char c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}

static void	append_module(t_module **lst, t_module *new)
{
	t_module	*temp;

	if (!*lst)
		*lst = new;
	else
	{
		temp = *lst;
		while (temp->next)
			temp = temp->next;
		temp->next = new;
	}
}

void	init_modules(char *input, t_shell *ms)
{
	char		*temp;
	t_module	*mod;

	while (*input)
	{
		while (ft_isspace(*input))
			input++;
		temp = ft_strchr(input, '|');
		if (!temp)
			temp = input + ft_strlen(input);
		mod = safe_calloc(sizeof(t_module), ms);
		safe_substr(&mod->input, input, temp, ms);
		append_module(&ms->mods, mod);
		if (invalid_syntax(input, mod, ms))
			break ;
		input = temp + 1;
	}
}

void	init_fds(t_descriptors *fds)
{
	if (!fds)
		return ;
	fds->pipe[WR_END] = -1;
	fds->pipe[RD_END] = -1;
	fds->in = -1;
	fds->out = -1;
}

void	init_minishell(t_shell *ms)
{
	ft_bzero(ms, sizeof(t_shell));
	init_fds(ms->fds);
	ms->envp = init_envp(0, 0, ms);
	safe_strdup(&ms->prompt, "[ minishell ]$ ", ms);
	ms->excode = SUCCESS;
}