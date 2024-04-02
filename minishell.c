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
		i = 0;
		printf("MODULE [%d]\n", j);
		printf("INPUT: %s\n", module->input);
		printf("INFILES:\n");
		parse = module->infiles;
		while (parse)
		{
			printf("infile[%d] %s\n", i, parse->content);
			parse = parse->next;
			i++;
		}
		printf("\n");
		if (module->next)
			printf("\nNext Module!\n\n");
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
		free_runtime(&ms);
	}
	return (ms.excode);
}
