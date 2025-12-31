/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jankku <jankku@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 00:00:00 by jankku            #+#    #+#             */
/*   Updated: 2025/01/01 00:00:00 by jankku           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <builtin.h>

int	builtin_pwd(t_vec *args, t_shell *shell)
{
	char	cwd[PATH_MAX];

	(void)args;
	(void)shell;
	if (!getcwd(cwd, sizeof(cwd)))
	{
		print_error_errno("pwd");
		return (EC_FAILURE);
	}
	ft_putendl_fd(cwd, STDOUT_FILENO);
	return (EC_SUCCESS);
}
