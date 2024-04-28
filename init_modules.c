/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_modules.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 18:35:52 by jmertane          #+#    #+#             */
/*   Updated: 2024/04/27 15:49:02 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	command_count(t_module *mod)
{
	int	len;

	len = 0;
	while (mod)
	{
		mod = mod->next;
		len++;
	}
	return (len);
}

static void	finalize_shell(t_shell *ms)
{
	ms->forks = command_count(ms->mods);
	ms->pids = safe_calloc(ms->forks * sizeof(pid_t), ms);
}

static void	finalize_module(t_module *mod)
{
	mod->outfd = -1;
	mod->infd = -1;
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

int	init_modules(char *input, t_shell *ms)
{
	char		*temp;
	t_module	*new;

	if (!input || !*input || error_syntax(ms->input, ms))
		return (FAILURE);
	while (*input)
	{
		while (ft_isspace(*input))
			input++;
		temp = ft_strchr(input, PIPE);
		if (!temp)
			temp = input + ft_strlen(input);
		new = safe_calloc(sizeof(t_module), ms);
		safe_substr(&new->input, input, temp, ms);
		append_module(&ms->mods, new);
		if (error_syntax(new->input, ms))
			return (FAILURE);
		finalize_module(new);
		input = temp + 1;
	}
	finalize_shell(ms);
	return (SUCCESS);
}
