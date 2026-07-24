/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: outaouss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/25 00:02:18 by outaouss          #+#    #+#             */
/*   Updated: 2026/07/25 00:02:20 by outaouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "codexion.h"

int check_burnout(t_sim *sim)
{
    int i = 0;
    long time_since;

    while (i < sim->number_of_coders)
    {
        pthread_mutex_lock(&sim->coders[i].c_mutex);

        time_since = get_time() - sim->coders[i].last_compile_start;

        if (time_since >= sim->time_to_burnout)
        {
            pthread_mutex_lock(&sim->stop_mutex);
            sim->stop_flag = 1;
            pthread_mutex_unlock(&sim->stop_mutex);

            pthread_mutex_lock(&sim->print_mutex);
            printf("%ld %d burned out\n", get_time() - sim->start_time, sim->coders[i].id);
            pthread_mutex_unlock(&sim->print_mutex);

            pthread_mutex_unlock(&sim->coders[i].c_mutex);
            return (1);
        }
        pthread_mutex_unlock(&sim->coders[i].c_mutex);
        i++;
    }
    return (0);
}

int check_all_compiled(t_sim *sim)
{
    int i = 0;
    int finished_coders = 0;

    // already catched in parsing tanrj3 liha
    if (sim->number_of_compiles_required <= 0)
        return (0);
    
    while (i < sim->number_of_coders)
    {
        pthread_mutex_lock(&sim->coders[i].c_mutex);

        if (sim->coders[i].compile_count >= sim->number_of_compiles_required)
            finished_coders++;
        
        pthread_mutex_unlock(&sim->coders[i].c_mutex);
        i++;
    }
    if (finished_coders == sim->number_of_coders)
    {
        pthread_mutex_lock(&sim->stop_mutex);
        sim->stop_flag = 1;
        pthread_mutex_unlock(&sim->stop_mutex);
        return (1);
    }
    return (0);
}

void *monitor_thread(void *arg)
{
    t_sim *sim;
    sim = (t_sim *)arg;

    while(1)
    {
        if (check_burnout(sim) == 1)
            return (NULL);
        if (check_all_compiled(sim) == 1)
            return (NULL);
        usleep(100);
    }
}