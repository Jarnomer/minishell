/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jankku <jankku@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 00:00:00 by jankku            #+#    #+#             */
/*   Updated: 2025/01/01 00:00:00 by jankku           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <builtin.h>

static void	print_export_entry(const char *entry)
{
	size_t	i;
	bool	in_value;

	ft_putstr_fd("declare -x ", STDOUT_FILENO);
	i = 0;
	in_value = false;
	while (entry[i])
	{
		ft_putchar_fd(entry[i], STDOUT_FILENO);
		if (entry[i] == '=' && !in_value)
		{
			ft_putchar_fd('"', STDOUT_FILENO);
			in_value = true;
		}
		i++;
	}
	if (in_value)
		ft_putchar_fd('"', STDOUT_FILENO);
	ft_putchar_fd('\n', STDOUT_FILENO);
}

static void	print_sorted_env(t_shell *shell)
{
	char	**sorted;
	size_t	i;

	sorted = safe_calloc(sizeof(char *) * (shell->env.len + 1));
	i = 0;
	while (i < shell->env.len)
	{
		sorted[i] = vec_get(&shell->env, i);
		i++;
	}
	sort_str_arr(sorted, shell->env.len);
	i = 0;
	while (i < shell->env.len)
	{
		print_export_entry(sorted[i]);
		i++;
	}
	free(sorted);
}

static int	export_one(const char *arg, t_shell *shell)
{
	char	*eq;
	size_t	name_len;
	char	*name;
	char	*value;

	eq = ft_strchr(arg, '=');
	if (eq)
		name_len = eq - arg;
	else
		name_len = ft_strlen(arg);
	if (!is_valid_identifier(arg, name_len))
	{
		ft_dprintf(STDERR_FILENO, "%sexport: `%s': %s\n",
			ERR_PROMPT, arg, ERR_MSG_IDFIER);
		return (EC_FAILURE);
	}
	if (!eq)
		return (EC_SUCCESS);
	name = safe_substr(arg, 0, name_len);
	value = safe_strdup(eq + 1);
	env_set(shell, name, value);
	free(name);
	free(value);
	return (EC_SUCCESS);
}

int	builtin_export(t_vec *args, t_shell *shell)
{
	size_t	i;
	int		status;
	int		ret;

	if (args->len == 1)
	{
		print_sorted_env(shell);
		return (EC_SUCCESS);
	}
	status = EC_SUCCESS;
	i = 1;
	while (i < args->len)
	{
		ret = export_one(vec_get(args, i), shell);
		if (ret != EC_SUCCESS)
			status = ret;
		i++;
	}
	return (status);
}
