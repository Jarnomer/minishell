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

int	check_cmd_error(const char *path)
{
	struct stat	st;

	if (!path || !*path)
	{
		print_error_cmd("", ERR_MSG_CMD);
		return (EC_NOTFOUND);
	}
	if (stat(path, &st) == -1)
	{
		print_error_cmd((char *)path, ERR_MSG_NOFILE);
		return (EC_NOTFOUND);
	}
	if (S_ISDIR(st.st_mode))
	{
		print_error_cmd((char *)path, ERR_MSG_ISDIR);
		return (EC_NOEXEC);
	}
	if (access(path, X_OK) == -1)
	{
		print_error_cmd((char *)path, ERR_MSG_PERM);
		return (EC_NOEXEC);
	}
	return (EC_SUCCESS);
}
