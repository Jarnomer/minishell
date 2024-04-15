/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 18:32:23 by jmertane          #+#    #+#             */
/*   Updated: 2024/04/09 19:04:09 by jmertane         ###   ########.fr       */
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

// static void	print_inputs(t_module **lst)
// {
// 	t_module	*module;
// 	t_parser	*parse;
// 	int			i;
// 	int			j;

// 	j = 0;
// 	module = *lst;
// 	while (module)
// 	{
// 		printf("\n==========\n");
// 		printf("MODULE [%d]\n", j);
// 		printf("==========\n\n");
// 		printf("INPUT: %s\n", module->input);
// 		i = 0;
// 		parse = module->command;
// 		while (parse)
// 		{
// 			if (!i)
// 			{
// 				printf("COMMAND:\n");
// 				printf("Executable: %s\n", parse->content);
// 			}
// 			else
// 				printf("Argument[%d]: %s\n", i, parse->content);
// 			parse = parse->next;
// 			i++;
// 		}
// 		i = 0;
// 		parse = module->infiles;
// 		while (parse)
// 		{
// 			if (!i)
// 				printf("INFILES:\n");
// 			if (parse->mode == INFILE)
// 				printf("Infile: %s\n", parse->content);
// 			else
// 				printf("Heredoc[EOF]: %s\n", parse->content);
// 			parse = parse->next;
// 			i++;
// 		}
// 		i = 0;
// 		parse = module->outfiles;
// 		while (parse)
// 		{
// 			if (!i)
// 				printf("OUTFILES:\n");
// 			if (parse->mode == OUTFILE)
// 				printf("Outfile: %s\n", parse->content);
// 			else
// 				printf("Append: %s\n", parse->content);
// 			parse = parse->next;
// 			i++;
// 		}
// 		module = module->next;
// 		j++;
// 	}
// }

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
		if (!ms.input || !ft_strncmp(ms.input, "exit", 5))
			break ;
		add_history(ms.input);
		if (init_modules(ms.input, &ms) == SUCCESS)
		{
			parse_inputs(&ms.mods, &ms);
			//print_inputs(&ms.mods);
			//execute_test(&ms);
			//check_files(&ms);
			// print_inputs(&ms.mods);
			execute_children(&ms);
			wait_children(&ms);
		}
		free_runtime(&ms);
	}
	free_exit(&ms);
	return (ms.excode);
}
