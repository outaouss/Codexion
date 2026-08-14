/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   donglesv2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: outaouss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 06:21:10 by outaouss          #+#    #+#             */
/*   Updated: 2026/08/04 06:21:11 by outaouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	is_dongle_ready(t_dongle *dongle, t_coder *coder)
{
	if ((t_coder *)dongle->heap.array[0] != coder)
		return (1);
	if (dongle->available_at > (long)get_time())
		return (1);
	if (dongle->in_process == 1)
		return (1);
	return (0);
}

void	dongle_take_helper(t_coder *coder)
{
	while (check_stop_flag(coder->data) == 0)
	{
		if (request_dongles(coder) == 0)
		{
			print_action(coder, "has taken a dongle");
			print_action(coder, "has taken a dongle");
			break ;
		}
		usleep(100);
	}
}

int	try_take_dongles(t_dongle *first, t_dongle *second, t_coder *coder)
{
	pthread_mutex_lock(&first->d_mutex);
	pthread_mutex_lock(&second->d_mutex);
	if (is_dongle_ready(first, coder) == 0
		&& is_dongle_ready(second, coder) == 0)
	{
		first->in_process = 1;
		second->in_process = 1;
		pop(&first->heap);
		pop(&second->heap);
		pthread_mutex_unlock(&second->d_mutex);
		pthread_mutex_unlock(&first->d_mutex);
		return (0);
	}
	pthread_mutex_unlock(&second->d_mutex);
	pthread_mutex_unlock(&first->d_mutex);
	return (1);
}
