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
    
    while(1)
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
