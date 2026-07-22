/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: outaouss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/22 00:20:23 by outaouss          #+#    #+#             */
/*   Updated: 2026/07/22 00:20:25 by outaouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void swap_nodes(int *a, int *b)
{
    int temp;

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
        if (heap->array[parent] > heap->array[i])
            swap_nodes(heap->array + parent, heap->array + i);
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
        if (r_child < heap->count && heap->array[l_child] > heap->array[r_child])
            best_child = r_child;
        if (heap->array[best_child] < heap->array[i])
        {
            swap_nodes(heap->array + best_child, heap->array + i);
            i = best_child;
        }
        else
            break;
    }
}

void push(t_heap *heap, int coder_id)
{
}

int pop(t_heap *heap)
{
}