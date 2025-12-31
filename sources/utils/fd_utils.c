/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jankku <jankku@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 00:00:00 by jankku            #+#    #+#             */
/*   Updated: 2025/01/01 00:00:00 by jankku           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*
** Close a file descriptor safely (ignores invalid fds)
*/
void	safe_close(int fd)
{
	if (fd >= 0)
		close(fd);
}

/*
** Close both ends of a pipe
*/
void	close_pipe(int pipefd[2])
{
	safe_close(pipefd[0]);
	safe_close(pipefd[1]);
}
