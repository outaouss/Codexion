/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: outaouss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 03:08:15 by outaouss          #+#    #+#             */
/*   Updated: 2026/08/04 03:08:17 by outaouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	coder_prepare(t_coder *coder)
{
	pthread_mutex_lock(&coder->data->start_mutex);
	while (!coder->data->simulation_started)
		pthread_cond_wait(&coder->data->start_cond, &coder->data->start_mutex);
	pthread_mutex_unlock(&coder->data->start_mutex);
	if (coder->id % 2 == 0)
		c_sleep(((coder->data->time_to_compile
					+ coder->data->dongle_cooldown) / 2), coder->data);
	pthread_mutex_lock(&coder->c_mutex);
	coder->last_compile_start = get_time();
	pthread_mutex_unlock(&coder->c_mutex);
}

void	coder_compile_loop(t_coder *coder)
{
	while (check_stop_flag(coder->data) == 0)
	{
		take_dongles(coder);
		if (check_stop_flag(coder->data))
			break ;
		do_compile(coder);
		release_dongles(coder);
		pthread_mutex_lock(&coder->c_mutex);
		coder->compile_count++;
		pthread_mutex_unlock(&coder->c_mutex);
		do_rest_and_refactor(coder);
	}
}

void	*coder_routine(void *arg)
{
	t_coder	*coder;

	coder = (t_coder *)arg;
	coder_prepare(coder);
	coder_compile_loop(coder);
	return (NULL);
}
