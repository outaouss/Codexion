/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: splinta <splinta@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/23 16:52:24 by splinta           #+#    #+#             */
/*   Updated: 2026/07/27 01:55:50 by splinta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void *coder_routine(void *arg)
{
    t_coder *coder;

    coder = (t_coder *)arg;

    pthread_mutex_lock(&coder->data->start_mutex);
    while (!coder->data->simulation_started)
    {
        pthread_cond_wait(&coder->data->start_cond, &coder->data->start_mutex);
    }
    pthread_mutex_unlock(&coder->data->start_mutex);

    if (coder->id % 2 == 0)
        // usleep((coder->data->time_to_compile + coder->data->dongle_cooldown) / 2);
        c_sleep(((coder->data->time_to_compile + coder->data->dongle_cooldown) / 2), coder->data);
    
    pthread_mutex_lock(&coder->c_mutex);
    coder->last_compile_start = get_time();
    pthread_mutex_unlock(&coder->c_mutex);

    while(check_stop_flag(coder->data) == 0)
    {
        take_dongles(coder);

        if (check_stop_flag(coder->data))
            break;

        do_compile(coder);
        release_dongles(coder);
        pthread_mutex_lock(&coder->c_mutex);
        coder->compile_count++;
        pthread_mutex_unlock(&coder->c_mutex);
        do_rest_and_refactor(coder);
    }
    return (NULL);
}

int start_simulation(t_sim *sim)
{
    int i;
    pthread_t monitor;

    i = 0;
    while(i < sim->number_of_coders)
    {
        int ret = pthread_create(&sim->coders[i].thread, NULL, &coder_routine, &sim->coders[i]);

        if (ret != 0)
        {
            fprintf(stderr, "=== Error: While Creating THREAD :%d ===\n", i);

            pthread_mutex_lock(&sim->stop_mutex);
            sim->stop_flag = 1;
            pthread_mutex_unlock(&sim->stop_mutex);

            pthread_mutex_lock(&sim->start_mutex);
            sim->simulation_started = 1;
            pthread_cond_broadcast(&sim->start_cond);
            pthread_mutex_unlock(&sim->start_mutex);

            while (i > 0)
            {
                i--;
                pthread_join(sim->coders[i].thread, NULL);
            }
            return (1);
        }
        i++;
    }
    if (pthread_create(&monitor, NULL, &monitor_thread, sim) != 0)
    {
        fprintf(stderr, "=== Error: While Creating MONITOR_THREAD ===\n");

        pthread_mutex_lock(&sim->stop_mutex);
        sim->stop_flag = 1;
        pthread_mutex_unlock(&sim->stop_mutex);

        pthread_mutex_lock(&sim->start_mutex);
        sim->simulation_started = 1;
        pthread_cond_broadcast(&sim->start_cond);
        pthread_mutex_unlock(&sim->start_mutex);

        while (i > 0)
        {
            i--;
            pthread_join(sim->coders[i].thread, NULL);
        }
        return (1);
    }

    sim->start_time = get_time();
    i = 0;
    while (i < sim->number_of_coders)
    {
        sim->coders[i].last_compile_start = sim->start_time;
        i++;
    }

    pthread_mutex_lock(&sim->start_mutex);
    sim->simulation_started = 1;
    pthread_cond_broadcast(&sim->start_cond);
    pthread_mutex_unlock(&sim->start_mutex);

    pthread_join(monitor, NULL);

    i = 0;
    while (i < sim->number_of_coders)
    {
        pthread_join(sim->coders[i].thread, NULL);
        i++;
    }
    return (0);
}
