#include "minishell.h"

static char	*parse_command(char * argv, t_module *mod, t_shell *ms)
{
	argv = handle_command(argv, mod, ms);
	return (argv);
}

static char	*parse_outfile(char *argv, t_module *mod, t_shell *ms)
{
	int		mode;

	argv = handle_outfile(argv, &mode, mod, ms);
	open_file(&mod->outfiles, mode);
	return (argv);
}

static char	*parse_infile(char *argv, t_module *mod, t_shell *ms)
{
	int		mode;

	argv = handle_infile(argv, &mode, mod, ms);
	open_file(&mod->infiles, mode);
	return (argv);
}

void	parse_inputs(t_module **lst, t_shell *ms)
{
	t_module	*mod;
	char		*input;

	mod = *lst;
	while (mod)
	{
		input = mod->input;
		while (*input)
		{
			while (ft_isspace(*input))
				input++;
			if (*input == '<')
				input = parse_infile(input, mod, ms);
			else if (*input == '>')
				input = parse_outfile(input, mod, ms);
			else
				input = parse_command(input, mod, ms);
		}
		mod = mod->next;
	}
}
