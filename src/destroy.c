/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: outaouss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/28 01:35:24 by outaouss          #+#    #+#             */
/*   Updated: 2026/07/28 01:35:26 by outaouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "codexion.h"

void destroy_sim_mutex(t_sim *sim)
{
    pthread_mutex_destroy(&sim->stop_mutex);
    pthread_mutex_destroy(&sim->print_mutex);
    pthread_cond_destroy(&sim->start_cond);
    pthread_mutex_destroy(&sim->start_mutex);
}

void destroy_coders_mutex(t_sim *sim)
{
    int i;

    i = 0;
    while (i < sim->number_of_coders)
    {
        pthread_mutex_destroy(&sim->coders[i].c_mutex);
        i++;
    }
}

void destroy_dongles_mutex(t_sim *sim)
{
    int i;

    i = 0;
    while (i < sim->number_of_coders)
    {
        pthread_mutex_destroy(&sim->dongles[i].d_mutex);
        i++;
    }
}