/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: outaouss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 06:22:30 by outaouss          #+#    #+#             */
/*   Updated: 2026/08/04 06:22:32 by outaouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	print_action(t_coder *coder, char *status)
{
	size_t	timestamp;

	pthread_mutex_lock(&coder->data->print_mutex);
	if (check_stop_flag(coder->data) == 0)
	{
		timestamp = get_time() - coder->data->start_time;
		printf("%ld %d %s\n", timestamp, coder->id, status);
	}
	pthread_mutex_unlock(&coder->data->print_mutex);
}

int	check_stop_flag(t_sim *sim)
{
	int	status;

	pthread_mutex_lock(&sim->stop_mutex);
	status = sim->stop_flag;
	pthread_mutex_unlock(&sim->stop_mutex);
	return (status);
}
