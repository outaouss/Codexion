/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: outaouss <outaouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/21 20:24:30 by outaouss          #+#    #+#             */
/*   Updated: 2026/07/21 22:43:54 by outaouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int init_heaps(t_sim *sim)
{
    int i = 0;
    
    while (i < sim->number_of_coders)
    {
        // sim->dongles[i].heap.array = malloc(sizeof(int) * 2);
        // if (!sim->dongles[i].heap.array)
        // {
        //     fprintf(stderr, "Error While Allocating !!!");
        //     free_heaps_so_far(sim, i);
        //     return (0);
        // }
        sim->dongles[i].heap.capacity = 2;
        sim->dongles[i].heap.count = 0;
        i++;
    }
    return (1);
}

int init_simulation(t_sim *sim)
{
    int i = 0;

    sim->coders = malloc(sizeof(t_coder) * sim->number_of_coders);
    if (!sim->coders)
    {
        fprintf(stderr, "Error While Allocating !!!");
        return (0);
    }
    sim->dongles = malloc(sizeof(t_dongle) * sim->number_of_coders);
    if (!sim->dongles)
    {
        fprintf(stderr, "Error While Allocating !!!");
        free(sim->coders);
        return (0);
    }
    while(i < sim->number_of_coders)
    {
        if(pthread_mutex_init(&sim->dongles[i].d_mutex, NULL))
        {
            while(i--)
            {
                pthread_mutex_destroy(&sim->dongles[i].d_mutex);
            }
            free(sim->coders);
            free(sim->dongles);
            return (0);
        }
        sim->dongles[i].available_at = 0;
        sim->dongles[i].in_process = 0;
        i++;
    }
    i = 0;
    while (i < sim->number_of_coders)
    {
        sim->coders[i].id = i + 1;
        sim->coders[i].compile_count = 0;
        sim->coders[i].data = sim;
        sim->coders[i].last_compile_start = 0;
        pthread_mutex_init(&sim->coders[i].c_mutex, NULL);

        sim->coders[i].left = &sim->dongles[i];
        sim->coders[i].right = &sim->dongles[(i + 1) % sim->number_of_coders];
        i++;
    }
    pthread_mutex_init(&sim->print_mutex, NULL);
    sim->stop_flag = 0;
    if (init_heaps(sim) == 0)
    {
        i = 0;
        while(i < sim->number_of_coders)
        {
            pthread_mutex_destroy(&sim->dongles[i].d_mutex);
            pthread_mutex_destroy(&sim->coders[i].c_mutex);
            i++;
        }
        free(sim->coders);
        free(sim->dongles);
        return (0);
    }
    return (1);
}
