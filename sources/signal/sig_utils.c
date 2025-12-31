/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jankku <jankku@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 00:00:00 by jankku            #+#    #+#             */
/*   Updated: 2025/01/01 00:00:00 by jankku           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sig.h>

/*
** Convert wait() status to shell exit code
** Handles both normal exit and signal termination
*/
int	get_exit_status(int status)
{
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGINT)
			ft_putchar_fd('\n', STDOUT_FILENO);
		if (WTERMSIG(status) == SIGQUIT)
			ft_putendl_fd(ERR_MSG_COREDUMP, STDERR_FILENO);
		return (EC_SIGNAL + WTERMSIG(status));
	}
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (EC_FAILURE);
}

int	check_signal_received(void)
{
	return (g_signal != 0);
}

void	reset_signal(void)
{
	g_signal = 0;
}
