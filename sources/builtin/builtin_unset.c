/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jankku <jankku@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 00:00:00 by jankku            #+#    #+#             */
/*   Updated: 2025/01/01 00:00:00 by jankku           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <builtin.h>

static int	unset_one(const char *name, t_shell *shell)
{
	if (!name || !is_valid_identifier(name, ft_strlen(name)))
	{
		ft_dprintf(STDERR_FILENO, "%sunset: `%s': not a valid identifier\n",
			ERR_PROMPT, name);
		return (EC_FAILURE);
	}
	env_unset(shell, name);
	return (EC_SUCCESS);
}

int	builtin_unset(t_vec *args, t_shell *shell)
{
	size_t	i;
	int		status;
	int		ret;

	status = EC_SUCCESS;
	i = 1;
	while (i < args->len)
	{
		ret = unset_one(vec_get(args, i), shell);
		if (ret != EC_SUCCESS)
			status = ret;
		i++;
	}
	return (status);
}
