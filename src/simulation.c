/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: splinta <splinta@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/23 16:52:24 by splinta           #+#    #+#             */
/*   Updated: 2026/07/24 03:39:00 by splinta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void *coder_routine(void *arg)
{
    t_coder *coder;

    coder = (t_coder *)arg;

    if (coder->id % 2 == 0)
        usleep(1000);
    
    while(1)
    {
        pthread_mutex_lock(&coder->left->d_mutex);
        pthread_mutex_lock(&coder->right->d_mutex);
        // print taking dongle here
        pthread_mutex_lock(&coder->c_mutex);
        coder->last_compile_start = get_time();
        pthread_mutex_unlock(&coder->c_mutex);
        // print is compiling
        coder->compile_count++; 
        c_sleep(coder->data->time_to_compile);
        // We will need to add the dongle_cooldown logic here soon!
        pthread_mutex_unlock(&coder->left->d_mutex);
        pthread_mutex_unlock(&coder->right->d_mutex);
        // print is debuging
        c_sleep(coder->data->time_to_debug);
        // print is refactoring
        c_sleep(coder->data->time_to_refactor);
    }
    return (NULL);
}

int start_simulation(t_sim *sim)
{
    int i;

    i = 0;
    while(i < sim->number_of_coders)
    {
        if (pthread_create(&sim->coders[i].thread, NULL, &coder_routine, &sim->coders[i]) != 0)
        {
            fprintf(stderr, "Error While Creating The Thread\n");
            return (0);
        }
        i++;
    }
    i = 0;
    while (i < sim->number_of_coders)
    {
        pthread_join(sim->coders[i].thread, NULL);
        i++;
    }
    return (1);
}
