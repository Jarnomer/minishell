/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 17:35:47 by vkinaret          #+#    #+#             */
/*   Updated: 2024/03/28 20:01:13 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include "libft/libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <readline/readline.h>
#include <readline/history.h>

typedef struct	s_shell
{
	char	*prompt;
	char	*input;
	char	*output;
	char	**envp;
	int		envp_size;
}				t_shell;

//parser.c
char	*parse_input(t_shell *ms);

//builtin.c
int		check_if_builtin(t_shell *ms, char *cmd);
//void 	builtin_env(char **envp, int i, int j) static funct
//void	builtin_export(t_shell *ms, int i, int j) static funct
//void	builtin_unset(t_shell *ms, int i, int j) static funct
//int	name_exists(t_shell *ms, char *name) static funct

//envp.c
char	**init_envp(int i, int size, t_shell *ms);
void	envp_update(t_shell *ms, char *content);
void	envp_add(t_shell *ms, char *content);
void	envp_remove(t_shell *ms, char *content);
void	envp_print(char **envp, int envp_size, int i, int flag);

//cd.c
void	change_directory(char *cmd);

//free.c
void	free_struct(t_shell *ms);
void	free_envp(t_shell *ms);


#endif
