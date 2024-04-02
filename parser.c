/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkinaret <vkinaret@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 19:56:14 by vkinaret          #+#    #+#             */
/*   Updated: 2024/03/26 19:56:20 by vkinaret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_inputs(t_module **lst, t_shell *ms)
{
	t_module	*mod;
	t_parser	*temp;

	mod = *lst;
	while (mod)
	{
		temp = mod->parse;
		while (temp)
		{
			if (*temp->content == '\'')
				safe_strtrim(&temp->content, "\'", ms);
			else if (*temp->content == '\"')
				safe_strtrim(&temp->content, "\"", ms);
			temp = temp->next;
		}
		mod = mod->next;
	}
}
