/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/01 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	vec_clear(t_vec *v, void (*del)(void *))
{
	size_t	i;

	if (!v || !v->data)
		return ;
	if (del)
	{
		i = 0;
		while (i < v->len)
		{
			if (v->data[i])
				del(v->data[i]);
			i++;
		}
	}
	v->len = 0;
}

void	vec_free(t_vec *v, void (*del)(void *))
{
	if (!v)
		return ;
	vec_clear(v, del);
	free(v->data);
	v->data = NULL;
	v->cap = 0;
}

void	vec_swap(t_vec *vec, size_t i, size_t j)
{
	void	*temp;

	temp = vec->data[i];
	vec->data[i] = vec->data[j];
	vec->data[j] = temp;
}

void	vec_append(t_vec *dest, t_vec *src)
{
	size_t	i;

	i = 0;
	while (i < src->len)
	{
		vec_push(dest, src->data[i]);
		i++;
	}
}
