/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: outaouss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 06:20:33 by outaouss          #+#    #+#             */
/*   Updated: 2026/08/04 06:20:35 by outaouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	destroy_all_mutexes(t_sim *sim)
{
	int	i;

	pthread_mutex_destroy(&sim->stop_mutex);
	pthread_mutex_destroy(&sim->print_mutex);
	pthread_cond_destroy(&sim->start_cond);
	pthread_mutex_destroy(&sim->start_mutex);
	i = 0;
	while (i < sim->number_of_coders)
	{
		pthread_mutex_destroy(&sim->coders[i].c_mutex);
		pthread_mutex_destroy(&sim->dongles[i].d_mutex);
		i++;
	}
}
