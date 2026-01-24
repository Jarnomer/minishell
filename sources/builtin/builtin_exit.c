/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jankku <jankku@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 00:00:00 by jankku            #+#    #+#             */
/*   Updated: 2025/01/01 00:00:00 by jankku           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <builtin.h>

static long long	str_to_long_long(const char *str)
{
	long long	result;
	int			sign;
	size_t		i;

	result = 0;
	sign = 1;
	i = 0;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i])
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (result * sign);
}

static void	exit_with_code(t_shell *shell, int code)
{
	shell->running = false;
	shell->exit_status = code;
}

static int	handle_numeric_error(char *arg, t_shell *shell)
{
	ft_dprintf(STDERR_FILENO, "%sexit: %s: %s\n",
		ERR_PROMPT, arg, ERR_MSG_NUMARG);
	shell->exit_status = EC_SYNTAX;
	return (EC_SYNTAX);
}

int	builtin_exit(t_vec *args, t_shell *shell)
{
	char		*arg;
	long long	code;

	ft_dprintf(STDERR_FILENO, "exit\n");
	if (args->len == 1)
	{
		exit_with_code(shell, shell->exit_status);
		return (shell->exit_status);
	}
	arg = vec_get(args, 1);
	if (!is_numeric(arg) || is_overflow(arg))
		return (handle_numeric_error(arg, shell));
	if (args->len > 2)
	{
		ft_dprintf(STDERR_FILENO, "%sexit: %s\n", ERR_PROMPT, ERR_MSG_TOOMANY);
		return (EC_TOOMANY);
	}
	code = str_to_long_long(arg);
	exit_with_code(shell, (unsigned char)code);
	return ((unsigned char)code);
}
