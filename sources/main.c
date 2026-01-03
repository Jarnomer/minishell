/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/01 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>
#include <execute.h>
#include <lexer.h>
#include <parser.h>
#include <debug.h>
#include <sig.h>

static void	shell_cleanup(t_shell *shell)
{
	vec_free(&shell->env, free_str);
	rl_clear_history();
}

static void	run_shell(t_shell *shell)
{
	char	*line;

	while (shell->running)
	{
		line = readline(PROMPT);
		if (!line)
		{
			if (shell->interactive)
				printf("exit\n");
			break ;
		}
		if (*line)
		{
			add_history(line);
			execute_shell(shell, line);
		}
		free(line);
	}
}

static void	env_init(t_vec *env, char **envp)
{
	size_t	i;

	if (!envp)
		return ;
	i = 0;
	while (envp[i])
	{
		vec_push(env, safe_strdup(envp[i]));
		i++;
	}
}

static void	shell_init(t_shell *shell, char **envp)
{
	shell->env = vec_new(0);
	env_init(&shell->env, envp);
	shell->exit_status = 0;
	shell->interactive = isatty(STDIN_FILENO);
	shell->running = true;
	setup_signals_interactive();
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;

	shell_init(&shell, envp);
	if (argc > 1 && !ft_strcmp(argv[1], "-d"))
		run_debug(&shell);
	else
		run_shell(&shell);
	shell_cleanup(&shell);
	return (shell.exit_status);
}
