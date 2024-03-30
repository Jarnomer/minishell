#include "minishell.h"

static void print_inputs(t_module **lst)
{
	t_module	*module;
	t_parser	*parse;
	int			i;

	module = *lst;
	while (module)
	{
		i = 0;
		parse = module->parse;
		while (parse)
		{
			printf("[%d] %s ", i, parse->content);
			parse = parse->next;
			i++;
		}
		printf("\n");
		if (module->next)
			printf("\nNext Module!\n\n");
		module = module->next;
	}
}

int	main(void)
{
	t_shell	ms;

	init_minishell(&ms);
	while (true)
	{
		ms.input = readline(ms.prompt);
		if (!ms.input)
			break ;
		else
		{
			init_modules(ms.input, &ms);
			print_inputs(&ms.mods);
		}
		free_runtime(&ms);
	}
	return (0);
}
