/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/01 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VEC_H
# define VEC_H

# include <shell.h>

# define VEC_INIT_CAP 8

typedef struct s_vec
{
	void	**data;
	size_t	len;
	size_t	cap;
}	t_vec;

t_vec	vec_new(size_t init_cap);
bool	vec_push(t_vec *v, void *item);
void	*vec_pop(t_vec *v);
void	*vec_get(t_vec *v, size_t index);

void	vec_clear(t_vec *v, void (*del)(void *));
void	vec_free(t_vec *v, void (*del)(void *));
void	vec_swap(t_vec *vec, size_t i, size_t j);
void	vec_append(t_vec *dest, t_vec *src);
void	vec_remove(t_vec *v, size_t index, void (*del)(void *));

#endif
