/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: splinta <splinta@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/22 00:20:23 by outaouss          #+#    #+#             */
/*   Updated: 2026/07/27 01:19:02 by splinta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

// int	is_higher_priority(t_coder *a, t_coder *b)
// {
// 	if (a->data->scheduler_mode == 0)
// 	{
// 		if (a->request_time < b->request_time)
// 			return (1);
// 		return (0);
// 	}
// 	if (a->deadline < b->deadline)
// 		return (1);
// 	return (0);
// }

int is_higher_priority(t_coder *a, t_coder *b)
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
    }

    if (a->last_compile_start != b->last_compile_start)
        return (a->last_compile_start < b->last_compile_start);

    return (a->id < b->id);
}

void swap_nodes(t_coder **a, t_coder **b)
{
    t_coder *temp;

    temp = *a;
    *a = *b;
    *b = temp;
}

void bubble_up(t_heap *heap, int index)
{
    int parent;
    int i;

    i = index;
    while (i > 0)
    {
        parent = (i - 1) / 2;
        if (is_higher_priority(heap->array[i], heap->array[parent]))
            // swap_nodes(heap->array + parent, heap->array + i);
            swap_nodes((t_coder **)&heap->array[parent], (t_coder **)&heap->array[i]);
        else
            break;
        i = parent;
    }
}

void bubble_down(t_heap *heap, int index)
{
    int i;
    int l_child;
    int r_child;
    int best_child;

    i = index;
    while((i * 2) + 1 < heap->count)
    {
        l_child = i * 2 + 1;
        r_child = i * 2 + 2;

        best_child = l_child;
        if (r_child < heap->count && is_higher_priority(heap->array[r_child], heap->array[l_child]))
            best_child = r_child;
        if (is_higher_priority(heap->array[best_child], heap->array[i]))
        {
            // swap_nodes(heap->array + best_child, heap->array + i);
            swap_nodes((t_coder **)&heap->array[best_child], (t_coder **)&heap->array[i]);
            i = best_child;
        }
        else
            break;
    }
}

void push(t_heap *heap, t_coder *coder)
{
    if (heap->count == heap->capacity)
        return ;
    heap->array[heap->count] = coder;
    heap->count++;
    bubble_up(heap, heap->count - 1);
}

t_coder *pop(t_heap *heap)
{
    t_coder *top_coder;

    if (heap->count == 0)
        return (NULL);

    top_coder = heap->array[0];
    
    heap->count--;
    heap->array[0] = heap->array[heap->count];
    bubble_down(heap, 0);   
    return (top_coder); 
}
