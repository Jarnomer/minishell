/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkinaret <vkinaret@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 13:37:27 by vkinaret          #+#    #+#             */
/*   Updated: 2024/04/08 13:37:30 by vkinaret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtin_pwd(t_shell *ms)
{
	char	*str;
	char	buf[1000];

	str = getcwd(buf, 1000);
	if (str)
		ft_putendl_fd(str, 1);
	else
		ms->excode = 1;
}
