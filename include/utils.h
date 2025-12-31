/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jankku <jankku@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 00:00:00 by jankku            #+#    #+#             */
/*   Updated: 2025/01/01 00:00:00 by jankku           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <vec.h>

# include <stdbool.h>
# include <unistd.h>

/*
** Safe allocation functions (exit on failure)
*/
void	*safe_calloc(size_t size);
char	*safe_itoa(int num);
char	*safe_strdup(const char *s);
char	*safe_substr(const char *s, unsigned int start, size_t len);
char	*safe_strjoin(const char *s1, const char *s2);

/*
** System call wrappers (return -1 on failure)
*/
int		try_pipe(int pipefd[2]);
pid_t	try_fork(int *fds_to_close, int fd_count);
int		try_open(const char *path, int flags, int mode);
int		try_dup(int oldfd);
int		try_dup2(int oldfd, int newfd);

/*
** File descriptor utilities
*/
void	safe_close(int fd);
void	close_pipe(int pipefd[2]);

/*
** String/char utilities
*/
bool	is_metachar(char c);
bool	is_quote(char c);
bool	has_quotes(const char *value);
void	free_str(void *str);
char	**vec_to_arr(t_vec *vec);

#endif
