/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   try_sysc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/01 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	try_pipe(int pipefd[2])
{
	if (pipe(pipefd) == -1)
	{
		print_error_errno("pipe");
		return (-1);
	}
	return (0);
}

pid_t	try_fork(int *fds_to_close, int fd_count)
{
	pid_t	pid;
	int		i;

	pid = fork();
	if (pid == -1)
	{
		print_error_errno("fork");
		i = 0;
		while (i < fd_count)
		{
			safe_close(fds_to_close[i]);
			i++;
		}
	}
	return (pid);
}

int	try_open(const char *path, int flags, int mode)
{
	int	fd;

	fd = open(path, flags, mode);
	if (fd == -1)
		print_error_errno((char *)path);
	return (fd);
}

int	try_dup(int oldfd)
{
	int	newfd;

	newfd = dup(oldfd);
	if (newfd == -1)
		print_error_errno("dup");
	return (newfd);
}

int	try_dup2(int oldfd, int newfd)
{
	if (dup2(oldfd, newfd) == -1)
	{
		print_error_errno("dup2");
		return (-1);
	}
	return (0);
}
