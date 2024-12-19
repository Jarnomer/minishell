/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 13:37:27 by vkinaret          #+#    #+#             */
/*   Updated: 2024/05/05 15:52:56 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	builtin_pwd(t_shell *ms)
{
	char	*str;
	char	buf[1000];

	str = getcwd(buf, 1000);
	if (str)
	{
		ft_putendl_fd(str, 1);
		ms->exitcode = 0;
	}
	else
		ft_putendl_fd(ms->cwd, 1);
}
