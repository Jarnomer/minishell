/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jankku <jankku@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 00:00:00 by jankku            #+#    #+#             */
/*   Updated: 2025/01/01 00:00:00 by jankku           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_vec	vec_new(size_t init_cap)
{
	t_vec	v;

	if (init_cap == 0)
		init_cap = VEC_INIT_CAP;
	v.data = malloc(sizeof(void *) * init_cap);
	if (!v.data)
	{
		perror("minishell");
		exit(EXIT_FAILURE);
	}
	v.cap = init_cap;
	v.len = 0;
	return (v);
}

static bool	vec_grow(t_vec *v)
{
	void	**new_data;
	size_t	new_cap;
	size_t	i;

	new_cap = v->cap * 2;
	new_data = malloc(sizeof(void *) * new_cap);
	if (!new_data)
		return (false);
	i = 0;
	while (i < v->len)
	{
		new_data[i] = v->data[i];
		i++;
	}
	free(v->data);
	v->data = new_data;
	v->cap = new_cap;
	return (true);
}

bool	vec_push(t_vec *v, void *item)
{
	if (!v || !v->data)
		return (false);
	if (v->len >= v->cap)
	{
		if (!vec_grow(v))
		{
			perror("minishell");
			exit(EXIT_FAILURE);
		}
	}
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
