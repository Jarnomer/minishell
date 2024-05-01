/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_modules.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 18:35:52 by jmertane          #+#    #+#             */
/*   Updated: 2024/04/30 20:13:42 by jmertane         ###   ########.fr       */
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

static char	*find_endpoint(char *input)
{
	while (*input)
	{
		while (*input && *input != '\'' && *input != '\"' && *input != PIPE)
			input++;
		if (*input == '\'' || *input == '\"')
		{
			input++;
			while (*input && *input != '\'' && *input != '\"')
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
		safe_substr(&new->input, input, temp, ms);
		append_module(&ms->mods, new);
		if (error_syntax(new->input, ms))
			return (FAILURE);
		new->outfd = -1;
		new->infd = -1;
		input = temp;
		if (*input)
			input++;
	}
	ms->forks = command_count(ms->mods);
	ms->pids = safe_calloc(ms->forks * sizeof(pid_t), ms);
	return (SUCCESS);
}
