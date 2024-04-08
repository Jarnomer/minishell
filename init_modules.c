/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_modules.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 18:35:52 by jmertane          #+#    #+#             */
/*   Updated: 2024/04/06 14:18:38 by jmertane         ###   ########.fr       */
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
	t_module	*mod;

	if (!input || !*input || error_syntax(input, '|', ms))
		return (FAILURE);
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
		if (error_syntax(mod->input, 0, ms))
			return (FAILURE);
		input = temp + 1;
	}
	ms->cmds = command_count(ms->mods) - 1;
	ms->pids = safe_calloc(ms->cmds * sizeof(pid_t), ms);
	return (SUCCESS);
}
