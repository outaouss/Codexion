/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: outaouss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 06:21:17 by outaouss          #+#    #+#             */
/*   Updated: 2026/08/04 06:21:19 by outaouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	free_all(t_sim *sim)
{
	int	i;

	i = 0;
	if (sim->coders)
		free(sim->coders);
	if (sim->dongles)
		free(sim->dongles);
}
