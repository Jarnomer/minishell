/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jankku <jankku@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 00:00:00 by jankku            #+#    #+#             */
/*   Updated: 2025/01/01 00:00:00 by jankku           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <builtin.h>

static bool	is_n_flag(const char *arg)
{
	size_t	i;

	if (!arg || arg[0] != '-')
		return (false);
	i = 1;
	if (arg[i] == '\0')
		return (false);
	while (arg[i])
	{
		if (arg[i] != 'n')
			return (false);
		i++;
	}
	return (true);
}

static size_t	skip_flags(t_vec *args)
{
	size_t	i;
	char	*arg;

	i = 1;
	while (i < args->len)
	{
		arg = vec_get(args, i);
		if (!is_n_flag(arg))
			break ;
		i++;
	}
	return (i);
}

static void	print_args(t_vec *args, size_t start)
{
	char	*arg;
	size_t	i;

	i = start;
	while (i < args->len)
	{
		arg = vec_get(args, i);
		ft_putstr_fd(arg, STDOUT_FILENO);
		if (i + 1 < args->len)
			ft_putchar_fd(' ', STDOUT_FILENO);
		i++;
	}
}

int	builtin_echo(t_vec *args, t_shell *shell)
{
	size_t	start;
	bool	newline;

	(void)shell;
	start = skip_flags(args);
	newline = (start == 1);
	print_args(args, start);
	if (newline)
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (EC_SUCCESS);
}
