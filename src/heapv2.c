/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heapv2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: outaouss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 06:21:31 by outaouss          #+#    #+#             */
/*   Updated: 2026/08/04 06:21:33 by outaouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	bubble_up(t_heap *heap, int index)
{
	int	parent;
	int	i;

	i = index;
	while (i > 0)
	{
		parent = (i - 1) / 2;
		if (is_higher_priority(heap->array[i], heap->array[parent]))
			swap_nodes((t_coder **)&heap->array[parent],
				(t_coder **)&heap->array[i]);
		else
			break ;
		i = parent;
	}
}

void	bubble_down(t_heap *heap, int index)
{
	int	i;
	int	l_child;
	int	r_child;
	int	best;

	i = index;
	while ((i * 2) + 1 < heap->count)
	{
		l_child = i * 2 + 1;
		r_child = i * 2 + 2;
		best = l_child;
		if (r_child < heap->count
			&& is_higher_priority(heap->array[r_child], heap->array[l_child]))
			best = r_child;
		if (is_higher_priority(heap->array[best], heap->array[i]))
		{
			swap_nodes((t_coder **)&heap->array[best],
				(t_coder **)&heap->array[i]);
			i = best;
		}
		else
			break ;
	}
}
