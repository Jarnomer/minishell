/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   try_sysc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jankku <jankku@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 00:00:00 by jankku            #+#    #+#             */
/*   Updated: 2025/01/01 00:00:00 by jankku           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*
** Wrapper for pipe() in PARENT process
** Returns -1 on failure, 0 on success
** Caller should handle error (don't exit shell)
*/
int	try_pipe(int pipefd[2])
{
	if (pipe(pipefd) == -1)
	{
		print_error_errno("pipe");
		return (-1);
	}
	return (0);
}

/*
** Wrapper for fork() in PARENT process
** On failure: prints error, closes fds, returns -1
** Caller should handle error (don't exit shell)
*/
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

/*
** Wrapper for open(), for redirections
** Prints error with filename on failure
** Returns fd on success, -1 on failure
*/
int	try_open(const char *path, int flags, int mode)
{
	int	fd;

	fd = open(path, flags, mode);
	if (fd == -1)
		print_error_errno((char *)path);
	return (fd);
}

/*
** Wrapper for dup() in PARENT process
** On failure: prints error, returns -1
*/
int	try_dup(int oldfd)
{
	int	newfd;

	newfd = dup(oldfd);
	if (newfd == -1)
		print_error_errno("dup");
	return (newfd);
}

/*
** Wrapper for dup2() in PARENT process
** On failure: prints error, returns -1
*/
int	try_dup2(int oldfd, int newfd)
{
	if (dup2(oldfd, newfd) == -1)
	{
		print_error_errno("dup2");
		return (-1);
	}
	return (0);
}
