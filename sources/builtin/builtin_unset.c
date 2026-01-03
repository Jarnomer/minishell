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

static void	unset_one(const char *name, t_shell *shell)
{
	if (!name || !is_valid_identifier(name, ft_strlen(name)))
		return ;
	env_unset(shell, name);
}

int	builtin_unset(t_vec *args, t_shell *shell)
{
	size_t	i;

	i = 1;
	while (i < args->len)
	{
		unset_one(vec_get(args, i), shell);
		i++;
	}
	return (EC_SUCCESS);
}
