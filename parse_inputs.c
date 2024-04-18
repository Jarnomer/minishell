/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_inputs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 18:32:53 by jmertane          #+#    #+#             */
/*   Updated: 2024/04/17 18:55:56 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_envp(t_parser *lst, int mode, t_shell *ms)
{
	char	*envp;

	if (!ft_strncmp(lst->content, "$?", 3))
		envp = safe_trash(ft_itoa(ms->excode), ALLOCATED, ms);
	else
	{
		envp = envp_exists(lst->content + 1, ms);
		if (!envp && mode != -1)
			return ;
	}
	free_single(&lst->content);
	safe_strdup(&lst->content, envp, ms);
}

void	parse_inputs(t_module **lst, t_shell *ms)
{
	t_module	*mod;
	char		*input;

	mod = *lst;
	while (mod)
	{
		input = mod->input;
		while (*input)
		{
			while (ft_isspace(*input))
				input++;
			if (!*input)
				break ;
			input = parse_argv(input, mod, ms);
		}
		mod = mod->next;
	}
}
