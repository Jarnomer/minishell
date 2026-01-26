/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/01 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <vec.h>

void	*safe_calloc(size_t size);
char	*safe_itoa(int num);
char	*safe_strdup(const char *s);
char	*safe_substr(const char *s, unsigned int start, size_t len);
char	*safe_strjoin(const char *s1, const char *s2);

int		try_pipe(int pipefd[2]);
pid_t	try_fork(int *fds_to_close, int fd_count);
int		try_open(const char *path, int flags, int mode);
int		try_dup(int oldfd);
int		try_dup2(int oldfd, int newfd);

void	safe_close(int fd);
void	close_pipe(int pipefd[2]);

bool	is_metachar(char c);
bool	is_quote(char c);
bool	has_quotes(const char *value);
char	**vec_to_arr(t_vec *vec);
void	free_arr(char **arr);

#endif
