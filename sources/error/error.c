/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/01 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <error.h>

static int	err_return(const char *cmd, const char *msg, int code)
{
	print_error_cmd((char *)cmd, (char *)msg);
	return (code);
}

int	check_cmd_error(const char *path)
{
	struct stat	st;

	if (!path || !*path)
		return (err_return("", ERR_MSG_CMD, EC_NOTFOUND));
	if (!ft_strchr(path, '/'))
		return (err_return(path, ERR_MSG_CMD, EC_NOTFOUND));
	if (stat(path, &st) == -1)
		return (err_return(path, ERR_MSG_NOFILE, EC_NOTFOUND));
	if (S_ISDIR(st.st_mode))
		return (err_return(path, ERR_MSG_ISDIR, EC_NOEXEC));
	if (access(path, X_OK) == -1)
		return (err_return(path, ERR_MSG_PERM, EC_NOEXEC));
	return (EC_SUCCESS);
}
