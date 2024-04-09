/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 18:36:13 by jmertane          #+#    #+#             */
/*   Updated: 2024/04/08 20:31:51 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error_child(char *s1, char *s2, t_module *mod)
{
	mod->errmsg[0] = s1;
	mod->errmsg[1] = ": ";
	mod->errmsg[2] = s2;
}

void	error_logger(char *msg1, char *msg2, char *msg3)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(BR, STDERR_FILENO);
	ft_putstr_fd(msg1, STDERR_FILENO);
	ft_putstr_fd(msg2, STDERR_FILENO);
	ft_putstr_fd(T, STDERR_FILENO);
	ft_putstr_fd(Y, STDERR_FILENO);
	ft_putendl_fd(msg3, STDERR_FILENO);
	ft_putstr_fd(T, STDERR_FILENO);
}

void	error_fatal(int errcode, char *errmsg, t_shell *ms)
{
	if (errmsg != NULL)
		perror(errmsg);
	// if (ms->idx != 0)
	// 	wait_children(ms);
	error_exit(errcode, ms);
}

void	error_exit(int errcode, t_shell *ms)
{
	free_exit(ms);
	exit(errcode);
}
