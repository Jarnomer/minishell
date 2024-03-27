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

static void	free_struct(t_shell *ms)
{
	int i;

	i = 0;
	if (ms->prompt)
		free(ms->prompt);
	if (ms->input)
		free(ms->input);
	while (i <= ms->envp_size)
	{
		free(ms->envp[i]);
		i++;
	}
	free(ms->envp);
}

//add a working history

static void	print_envp_alpha(char **envp, int envp_size)
{
	int i;

	i = 0;
	//this prints out the env list, but it should print it out alphabetically
	while (envp[i] != NULL && i < envp_size)
	{
		printf("%s\n", envp[i]);
		i++;
	}
}

static void	add_var_to_envp(t_shell *ms)
{
	int		i;
	char	*name;
	char	*temp;
	//char	*last_var;
	//char	**new_envp;

	i = 7;
	name = NULL;
	temp = NULL;
	//example: export name=content
	//find name first
	while (ms->input[i])
	{
		//loop until '=' is encountered
		if (ms->input[i] == '=')
			break ;
		//make a string called 'name'
		i++;
	}
	//check if name matches an existing variable
	//if name exists, replace the content with new input without adding a new item
	//if name doesn't exist, add ms->input as the (envp_size - 2)nth item
	printf("output: %s\n", ms->output);
}

static char	**init_envp(int i, int size, t_shell *ms)
{
	char		**envp;
	extern char	**environ;

	while (environ[size] != NULL)
		size++;
	ms->envp_size = size;
	envp = ft_calloc(size + 1, sizeof(char *));
	while (i < size)
	{
		envp[i] = ft_strdup(environ[i]);
		i++;
	}
	envp[i] = NULL;
	return (envp);
}

int	main(void)
{
	int i;
	t_shell	ms;

	ft_bzero(&ms, sizeof(t_shell));
	ms.prompt = ft_strdup("[ minishell ] ");
	ms.envp = init_envp(0, 0, &ms);
	while (true)
	{
		ms.input = readline(ms.prompt);
		if (!ms.input)
		{
			free_struct(&ms);
			printf("\nReceived EOF!\n");
			break ;
		}	
		//parse the input, use 'output' in struct to set the correct message (compare to bash)
		ms.output = parse_input(&ms);
		//check if input is 'history' (display history list except for the current line)
		//add history after checking history
		//check if input is 'exit'
		if (ft_strncmp("exit", ms.input, 5) == 0)
		{
			free_struct(&ms);
			printf("\nProgram ended successfully!\n");
			break ;
		}
		//check if input is 'env'
		else if (ft_strncmp("env", ms.input, 4) == 0)
		{
			i = 0;
			while (ms.envp[i] != NULL)
			{
				printf("%s\n", ms.envp[i]);
				i++;
			}
		}
		//check if input is 'export' + arguments
		else if (ft_strncmp("export", ms.input, 6) == 0)
		{
			//if no argument is given, print out the env list alphabetically
			if (ft_strncmp("export", ms.input, 7) == 0)
				print_envp_alpha(ms.envp, ms.envp_size);
			//the argument should be formatted 'name' or 'name=content' (checked by parser)
			//if name doesn't it will add the argument to the end of env list, before _
				//if no content is specified, it will appear as name='' on the env list
				//name='' will never be displayed by env, but they are displayed by export
			//if name exists, it will search and update its content
			else
				add_var_to_envp(&ms);
			//export can take multiple arguments so the add_var function should handle any number of them
		}
		//check if input is 'unset' + arguments
			//find the argument and remove it from the list
		//check if input is 'pwd'
		else if (ft_strncmp("pwd", ms.input, 4) == 0)
			printf("%s\n", getenv("PWD"));
		//check if input is 'cd' + relative/absolute path
		//check if input is 'echo' or 'echo -n'
		//print output
		else if (ms.output)
			printf("output: %s\n", ms.output);
		free(ms.input);
	}
	return (0);
}
