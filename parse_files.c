/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_files.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 14:10:32 by jmertane          #+#    #+#             */
/*   Updated: 2024/04/06 15:10:37 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	parse_outfiles(t_parser **lst, t_module *mod)
{
	t_parser	*temp;

	temp = *lst;
	while (temp)
	{
		temp = temp->next;
	}
}

static void	parse_infiles(t_parser **lst, t_module *mod)
{
	t_parser	*temp;

	temp = *lst;
	while (temp)
	{
		temp = temp->next;
	}
}

void	parse_files(t_module **lst, t_shell *ms)
{
	t_module	*mod;

	mod = *lst;
	while (mod)
	{
		parse_infiles(&mod->infiles, mod);
		parse_outfiles(&mod->outfiles, mod);
		mod = mod->next;
	}
}
