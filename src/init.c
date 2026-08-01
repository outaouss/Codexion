/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: splinta <splinta@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/21 20:24:30 by outaouss          #+#    #+#             */
/*   Updated: 2026/07/26 02:04:26 by splinta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int init_heaps(t_sim *sim)
{
    int i = 0;
    
    while (i < sim->number_of_coders)
    {
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
        return (1); 
    }
    sim->dongles = malloc(sizeof(t_dongle) * sim->number_of_coders);
    if (!sim->dongles)
    {
        fprintf(stderr, "Error While Allocating !!!");
        free(sim->coders);
        return (1);
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
            return (1);
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
        if (pthread_mutex_init(&sim->coders[i].c_mutex, NULL))
        {
            while (i--)
            {
                pthread_mutex_destroy(&sim->coders[i].c_mutex);
            }
            free(sim->coders);
            free(sim->dongles);
            return (1);
        }

        sim->coders[i].left = &sim->dongles[i];
        sim->coders[i].right = &sim->dongles[(i + 1) % sim->number_of_coders];
        i++;
    }
    pthread_mutex_init(&sim->print_mutex, NULL);

    pthread_mutex_init(&sim->start_mutex, NULL);
    pthread_cond_init(&sim->start_cond, NULL);

    sim->simulation_started = 0;
    sim->stop_flag = 0;
    init_heaps(sim);

    // if (init_heaps(sim) == 0)
    // {
    //     i = 0;
    //     while(i < sim->number_of_coders)
    //     {
    //          pthread_mutex_destroy(&sim->dongles[i].d_mutex);
    //         pthread_mutex_destroy(&sim->coders[i].c_mutex);
    //         i++;
    //     }
    //     free(sim->coders);
    //     free(sim->dongles);
    //     return (1);
    // }
    return (0);
}
