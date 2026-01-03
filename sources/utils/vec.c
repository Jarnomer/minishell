/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/01 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_vec	vec_new(size_t init_cap)
{
	t_vec	v;

	if (init_cap == 0)
		init_cap = VEC_INIT_CAP;
	v.data = safe_calloc(sizeof(void *) * init_cap);
	v.cap = init_cap;
	v.len = 0;
	return (v);
}

static void	vec_grow(t_vec *v)
{
	void	**new_data;
	size_t	new_cap;
	size_t	i;

	new_cap = v->cap * 2;
	new_data = safe_calloc(sizeof(void *) * new_cap);
	i = 0;
	while (i < v->len)
	{
		new_data[i] = v->data[i];
		i++;
	}
	free(v->data);
	v->data = new_data;
	v->cap = new_cap;
}

bool	vec_push(t_vec *v, void *item)
{
	if (!v || !v->data)
		return (false);
	if (v->len >= v->cap)
		vec_grow(v);
	v->data[v->len] = item;
	v->len++;
	return (true);
}

void	*vec_pop(t_vec *v)
{
	void	*item;

	if (!v || !v->data || v->len == 0)
		return (NULL);
	v->len--;
	item = v->data[v->len];
	v->data[v->len] = NULL;
	return (item);
}

void	*vec_get(t_vec *v, size_t index)
{
	if (!v || !v->data || index >= v->len)
		return (NULL);
	return (v->data[index]);
}
