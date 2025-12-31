/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jankku <jankku@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 00:00:00 by jankku            #+#    #+#             */
/*   Updated: 2025/01/01 00:00:00 by jankku           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <builtin.h>

static char	*get_cd_target(t_vec *args, t_shell *shell)
{
	char	*target;

	if (args->len == 1)
	{
		target = env_get(&shell->env, "HOME");
		if (!target)
		{
			ft_dprintf(STDERR_FILENO, "%scd: HOME %s\n",
				ERR_PROMPT, ERR_MSG_NOTSET);
			return (NULL);
		}
		return (target);
	}
	return (vec_get(args, 1));
}

static void	update_pwd_vars(t_shell *shell, const char *oldpwd)
{
	char	cwd[PATH_MAX];

	if (oldpwd)
		env_set(shell, "OLDPWD", oldpwd);
	if (getcwd(cwd, sizeof(cwd)))
		env_set(shell, "PWD", cwd);
}

int	builtin_cd(t_vec *args, t_shell *shell)
{
	char	*target;
	char	oldpwd[PATH_MAX];
	char	*saved_oldpwd;

	if (args->len > 2)
	{
		ft_dprintf(STDERR_FILENO, "%scd: %s\n", ERR_PROMPT, ERR_MSG_TOOMANY);
		return (EC_FAILURE);
	}
	target = get_cd_target(args, shell);
	if (!target)
		return (EC_FAILURE);
	saved_oldpwd = NULL;
	if (getcwd(oldpwd, sizeof(oldpwd)))
		saved_oldpwd = oldpwd;
	if (chdir(target) == -1)
	{
		ft_dprintf(STDERR_FILENO, "%scd: %s: %s\n",
			ERR_PROMPT, target, strerror(errno));
		return (EC_FAILURE);
	}
	update_pwd_vars(shell, saved_oldpwd);
	return (EC_SUCCESS);
}
