/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: outaouss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 06:21:25 by outaouss          #+#    #+#             */
/*   Updated: 2026/08/04 06:21:26 by outaouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	is_higher_priority(t_coder *a, t_coder *b)
{
	if (a->data->scheduler_mode == 0)
	{
		if (a->request_time != b->request_time)
			return (a->request_time < b->request_time);
	}
	else
	{
		if (a->deadline != b->deadline)
			return (a->deadline < b->deadline);
		if (a->deadline == b->deadline)
		{
			if (a->compile_count == b->compile_count)
				return (a->id < b->id);
			return (a->compile_count < b->compile_count);
		}
	}
	if (a->last_compile_start != b->last_compile_start)
		return (a->last_compile_start < b->last_compile_start);
	return (a->id < b->id);
}

void	swap_nodes(t_coder **a, t_coder **b)
{
	t_coder	*temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

void	push(t_heap *heap, t_coder *coder)
{
	if (heap->count == heap->capacity)
		return ;
	heap->array[heap->count] = coder;
	heap->count++;
	bubble_up(heap, heap->count - 1);
}

t_coder	*pop(t_heap *heap)
{
	t_coder	*top_coder;

	if (heap->count == 0)
		return (NULL);
	top_coder = heap->array[0];
	heap->count--;
	heap->array[0] = heap->array[heap->count];
	bubble_down(heap, 0);
	return (top_coder);
}
