/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: splinta <splinta@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/23 16:52:24 by splinta           #+#    #+#             */
/*   Updated: 2026/07/24 03:54:58 by splinta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void *coder_routine(void *arg)
{
    t_coder *coder;

    coder = (t_coder *)arg;

    if (coder->id % 2 == 0)
        usleep(1000);
    
    while(check_stop_flag(coder->data) == 0)
    {
        take_dongles(coder);
        do_compile(coder);
        release_dongles(coder);
        do_rest_and_refactor(coder);
    }
    return (NULL);
}

int start_simulation(t_sim *sim)
{
    int i;
    pthread_t monitor;

    i = 0;
    sim->start_time = get_time();
    while(i < sim->number_of_coders)
    {
        sim->coders[i].last_compile_start = sim->start_time;
        if (pthread_create(&sim->coders[i].thread, NULL, &coder_routine, &sim->coders[i]) != 0)
        {
            fprintf(stderr, "Error While Creating The Thread\n");
            while (i > 0)
            {
                i--;
                pthread_join(sim->coders[i].thread, NULL);
            }
            return (0);
        }
        i++;
    }
    if (pthread_create(&monitor, NULL, &monitor_thread, sim) != 0)
    {
        fprintf(stderr, "Error: While Creating Monitor Thread\n");
        pthread_mutex_lock(&sim->stop_mutex);
        sim->stop_flag = 1;
        pthread_mutex_unlock(&sim->stop_mutex);
    }
    else
    {
        pthread_join(monitor, NULL);
    }

    i = 0;
    while (i < sim->number_of_coders)
    {
        pthread_join(sim->coders[i].thread, NULL);
        i++;
    }
    return (1);
}
