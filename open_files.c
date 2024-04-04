/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 18:32:41 by jmertane          #+#    #+#             */
/*   Updated: 2024/04/04 18:35:38 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	open_file(t_parser **lst, int mode)
{
	t_parser	*temp;

	temp = *lst;
	while (temp->next)
		temp = temp->next;
	if (mode == -1)
	{
		temp->mode = -1;
		temp->fd = -1;
	}
	else
	{
		temp->mode = mode;
	}
}
