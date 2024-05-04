/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_modules.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 18:35:52 by jmertane          #+#    #+#             */
/*   Updated: 2024/05/04 12:09:56 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	command_count(t_module *mod)
{
	if (!mod)
		return (0);
	else
		return (1 + command_count(mod->next));
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

static char	*find_endpoint(char *input)
{
	while (*input)
	{
		while (*input && *input != SINGLEQUOTE
			&& *input != DOUBLEQUOTE && *input != PIPE)
			input++;
		if (*input == SINGLEQUOTE || *input == DOUBLEQUOTE)
		{
			input++;
			while (*input && *input != SINGLEQUOTE && *input != DOUBLEQUOTE)
				input++;
			input++;
		}
		else
			return (input);
	}
	return (input);
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
		temp = find_endpoint(input);
		new = safe_calloc(sizeof(t_module), ms);
		new->outfd = -1;
		new->infd = -1;
		safe_substr(&new->input, input, temp, ms);
		append_module(&ms->mods, new);
		if (error_syntax(new->input, ms))
			return (FAILURE);
		input = temp;
		if (*input)
			input++;
	}
	ms->forks = command_count(ms->mods);
	ms->pids = safe_calloc(ms->forks * sizeof(pid_t), ms);
	return (SUCCESS);
}
