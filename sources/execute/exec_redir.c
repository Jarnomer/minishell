/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/01 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <execute.h>

static int	apply_hdoc(t_redir *redir)
{
	if (redir->fd < 0)
		return (-1);
	if (try_dup2(redir->fd, STDIN_FILENO) == -1)
		return (-1);
	safe_close(redir->fd);
	redir->fd = -1;
	return (0);
}

static int	apply_redir(t_redir *redir)
{
	int	fd;
	int	target_fd;

	if (redir->type == REDIR_HEREDOC)
		return (apply_hdoc(redir));
	fd = open_redir_file(redir);
	if (fd == -1)
		return (-1);
	if (redir->type == REDIR_IN)
		target_fd = STDIN_FILENO;
	else
		target_fd = STDOUT_FILENO;
	if (try_dup2(fd, target_fd) == -1)
	{
		safe_close(fd);
		return (-1);
	}
	safe_close(fd);
	return (0);
}

int	apply_redirs(t_vec *redirs)
{
	t_redir	*redir;
	size_t	i;

	i = 0;
	while (i < redirs->len)
	{
		redir = vec_get(redirs, i);
		if (apply_redir(redir) == -1)
			return (-1);
		i++;
	}
	return (0);
}

int	save_std_fds(int saved_fds[2])
{
	saved_fds[0] = try_dup(STDIN_FILENO);
	if (saved_fds[0] == -1)
		return (-1);
	saved_fds[1] = try_dup(STDOUT_FILENO);
	if (saved_fds[1] == -1)
	{
		safe_close(saved_fds[0]);
		return (-1);
	}
	return (0);
}

void	restore_std_fds(int saved_fds[2])
{
	dup2(saved_fds[0], STDIN_FILENO);
	dup2(saved_fds[1], STDOUT_FILENO);
	safe_close(saved_fds[0]);
	safe_close(saved_fds[1]);
}
