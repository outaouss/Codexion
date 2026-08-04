/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: outaouss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 06:22:00 by outaouss          #+#    #+#             */
/*   Updated: 2026/08/04 06:22:02 by outaouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	main(int argc, char **argv)
{
	t_sim	sim;

	if (argc == 9)
	{
		if (parsing(argv, &sim))
			return (1);
		if (init_simulation(&sim))
			return (1);
		if (start_simulation(&sim))
		{
			destroy_all_mutexes(&sim);
			free_all(&sim);
			return (1);
		}
		free_all(&sim);
		destroy_all_mutexes(&sim);
	}
	else
	{
		fprintf(stderr, "Error: Inputs Must Be 8\nGot: [ %d ]\n", argc - 1);
		return (1);
	}
	return (0);
}
