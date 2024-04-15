/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 18:32:23 by jmertane          #+#    #+#             */
/*   Updated: 2024/04/14 18:15:31 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static void	check_files(t_shell *ms)
// {
// 	int infd = open_infile(ms->mods, ms);
// 	int outfd = open_outfile(ms->mods, ms);
// 	if (infd == -1)
// 		printf("Failed saving infd, %s, exit with ERR_FILE\n", strerror(errno));
// 	if (outfd == -1)
// 		printf("Failed saving outfd, %s, exit with ERR_FILE\n", strerror(errno));
// }

/*static void	print_inputs(t_module **lst)
{
	t_module	*module;
	t_parser	*parse;
	int			i;
	int			j;

	j = 0;
	module = *lst;
	while (module)
	{
		printf("\n==========\n");
		printf("MODULE [%d]\n", j);
		printf("==========\n\n");
		printf("INPUT: %s\n", module->input);
		i = 0;
		parse = module->command;
		while (parse)
		{
			if (!i)
			{
				printf("COMMAND:\n");
				printf("Executable(%d): %s\n", (int)ft_strlen(parse->content), parse->content);
			}
			else
				printf("Argument[%d](%d): %s\n", i, (int)ft_strlen(parse->content), parse->content);
			parse = parse->next;
			i++;
		}
		i = 0;
		parse = module->infiles;
		while (parse)
		{
			if (!i)
				printf("INFILES:\n");
			if (parse->mode == INFILE)
				printf("Infile(%d): %s\n", (int)ft_strlen(parse->content), parse->content);
			else
				printf("Heredoc[EOF](%d): %s\n", (int)ft_strlen(parse->content), parse->content);
			parse = parse->next;
			i++;
		}
		i = 0;
		parse = module->outfiles;
		while (parse)
		{
			if (!i)
				printf("OUTFILES:\n");
			if (parse->mode == OUTFILE)
				printf("Outfile(%d): %s\n", (int)ft_strlen(parse->content), parse->content);
			else
				printf("Append(%d): %s\n", (int)ft_strlen(parse->content), parse->content);
			parse = parse->next;
			i++;
		}
		module = module->next;
		j++;
	}
}

static void envp_imitation(t_shell *ms)
{
	t_module	*mod;

	mod = ms->mods;
	while (mod)
	{
		parse_envp(mod, ms);
		mod = mod->next;
	}
}*/

static void sigint_handler(int sign)
{
	if (sign == SIGINT)
	{
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		//printf("Control-C detected!\n");
		signal(SIGINT, SIG_IGN);
	}
}

static void init_signals(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}

int	main(void)
{
	t_shell	ms;

	init_shell(&ms);
	init_signals();
	while (true)
	{
		ms.input = readline(ms.prompt);
		if (!ms.input)
			break ;
		add_history(ms.input);
		if (!init_modules(ms.input, &ms))
		{
			parse_inputs(&ms.mods, &ms);
			//envp_imitation(&ms);
			//print_inputs(&ms.mods);
			//check_files(&ms);
			execute_children(&ms);
			wait_children(&ms);
		}
		free_runtime(&ms);
	}
	free_exit(&ms);
	return (NOERROR);
}
