/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkinaret <vkinaret@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 17:02:18 by vkinaret          #+#    #+#             */
/*   Updated: 2024/03/26 17:02:19 by vkinaret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//add a working history (should survive several instances)

static void	print_inputs(t_module **lst, t_shell *ms)
{
	t_module	*module;
	t_parser	*parse;
	int			i;
	int			j;

	j = 0;
	module = *lst;
	while (module)
	{
		i = 0;
		parse = module->parse;
		printf("MODULE [%d]\n", j);
		printf("INPUT: %s\n", module->input);
		//while (parse)
		//{
		//	printf("[%d]_%s_", i, parse->content);
		//	parse = parse->next;
		//	i++;
		//}
		ft_putstr_fd("OUTPUT:\n", 1);
		if (check_if_builtin(ms, module->input) == 1)
		{
			free_struct(ms);
			ft_putstr_fd("exit\n", 1);
			exit(1);
		}
		if (module->next)
			ft_putstr_fd("\n", 1);
		module = module->next;
		j++;
	}
}

static void	free_runtime(t_shell *ms)
{
	if (ms->input)
		free(ms->input);
	if (ms->mods)
		free_modules(&ms->mods);
	close_fds(ms->fds);
	init_fds(ms->fds);
}

int	main(void)
{
	t_shell	ms;

	init_minishell(&ms);
	while (true)
	{
		ms.input = readline(ms.prompt);
		if (!ms.input)
		{
			free_struct(&ms);
			printf("\nReceived EOF!\n");
			return (1);
		}
		add_history(ms.input);
		init_modules(ms.input, &ms);
		parse_inputs(&ms.mods, &ms);
		print_inputs(&ms.mods, &ms);
		free_runtime(&ms);
	}
	return (0);
}
