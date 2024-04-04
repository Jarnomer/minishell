/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 18:36:13 by jmertane          #+#    #+#             */
/*   Updated: 2024/04/04 18:36:15 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	error_exit(int errcode, char *errmsg, t_shell *ms)
{
	if (errmsg != NULL)
	{
		error_logger(errmsg, ": ", strerror(errno));
	}
	free_runtime(ms, FAILURE);
	exit(errcode);
}
