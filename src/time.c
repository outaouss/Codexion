/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: outaouss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/12 04:47:38 by outaouss          #+#    #+#             */
/*   Updated: 2026/08/12 04:47:40 by outaouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

size_t	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	c_sleep(size_t duration, t_sim *sim)
{
	size_t	start_time;

	start_time = get_time();
	while (!check_stop_flag(sim))
	{
		if (get_time() - start_time >= duration)
			break ;
		usleep(500);
	}
}
