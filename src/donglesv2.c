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
		return (0);
	if (dongle->available_at > (long)get_time())
		return (0);
	if (dongle->in_process == 1)
		return (0);
	return (1);
}

void	dongle_take_helper(t_coder *coder)
{
	while (check_stop_flag(coder->data) == 0)
	{
		if (request_dongles(coder) == 1)
		{
			print_action(coder, "has taken a dongle");
			print_action(coder, "has taken a dongle");
			break ;
		}
		usleep(100);
	}
}
