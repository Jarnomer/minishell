/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jankku <jankku@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 00:00:00 by jankku            #+#    #+#             */
/*   Updated: 2025/01/01 00:00:00 by jankku           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <builtin.h>

int	builtin_env(t_vec *args, t_shell *shell)
{
	size_t	i;

	if (args->len > 1)
	{
		ft_dprintf(STDERR_FILENO, "%senv: %s\n", ERR_PROMPT, ERR_MSG_TOOMANY);
		return (EC_FAILURE);
	}
	i = 0;
	while (i < shell->env.len)
	{
		ft_putendl_fd(vec_get(&shell->env, i), STDOUT_FILENO);
		i++;
	}
	return (EC_SUCCESS);
}
