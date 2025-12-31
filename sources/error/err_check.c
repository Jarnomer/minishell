/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jankku <jankku@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 00:00:00 by jankku            #+#    #+#             */
/*   Updated: 2025/01/01 00:00:00 by jankku           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*
** Check command path for errors and print appropriate message
** Returns: EC_SUCCESS (0), EC_NOEXEC (126), or EC_NOTFOUND (127)
*/
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

/*
** Convert t_err enum to corresponding error message string
** Returns pointer to static string (do not free)
*/
char	*err_to_msg(t_err err)
{
	if (err == ERR_CMD_NOT_FOUND)
		return (ERR_MSG_CMD);
	if (err == ERR_NO_SUCH_FILE)
		return (ERR_MSG_NOFILE);
	if (err == ERR_PERMISSION)
		return (ERR_MSG_PERM);
	if (err == ERR_IS_DIR)
		return (ERR_MSG_ISDIR);
	if (err == ERR_NOT_DIR)
		return (ERR_MSG_NOTDIR);
	if (err == ERR_AMBIG_REDIR)
		return (ERR_MSG_AMBIG);
	if (err == ERR_SYNTAX)
		return (ERR_MSG_SYNTAX);
	if (err == ERR_MALLOC)
		return (ERR_MSG_MALLOC);
	return (ERR_MSG_UNKNOWN);
}
