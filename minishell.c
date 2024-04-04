#include "minishell.h"
#include <stdio.h>

static void	print_inputs(t_module **lst)
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
				printf("Executable: %s\n", parse->content);
			}
			else
				printf("Argument[%d]: %s\n", i, parse->content);
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
				printf("Infile: %s\n", parse->content);
			else
				printf("Heredoc[EOF]: %s\n", parse->content);
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
				printf("Outfile: %s\n", parse->content);
			else
				printf("Append: %s\n", parse->content);
			parse = parse->next;
			i++;
		}
		module = module->next;
		j++;
	}
}

int	main(void)
{
	t_shell	ms;

	init_shell(&ms);
	while (true)
	{
		ms.input = readline(ms.prompt);
		if (!ms.input)
			break ;
		else
		{
			init_modules(ms.input, &ms);
			parse_inputs(&ms.mods, &ms);
			print_inputs(&ms.mods);
		}
		free_runtime(&ms, SUCCESS);
	}
	return (ms.excode);
}
