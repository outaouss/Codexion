/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_helpers2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: splinta <splinta@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/05 00:12:39 by outaouss          #+#    #+#             */
/*   Updated: 2026/08/07 06:56:30 by splinta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	destroy_sync_primitives(t_sim *sim, int count)
{
	if (count > 2)
		pthread_cond_destroy(&sim->start_cond);
	if (count > 1)
		pthread_mutex_destroy(&sim->start_mutex);
	if (count > 0)
		pthread_mutex_destroy(&sim->print_mutex);
}

void	abort_sync_init(t_sim *sim, int count)
{
	destroy_sync_primitives(sim, count);
	destroy_coder_mutexes(sim, sim->number_of_coders);
	destroy_dongle_mutexes(sim, sim->number_of_coders);
	free(sim->coders);
	free(sim->dongles);
}
