/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: splinta <splinta@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/20 01:52:47 by outaouss          #+#    #+#             */
/*   Updated: 2026/07/27 01:31:40 by splinta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	parsing(char **av, t_sim *sim)
{
	if (parsing_while(av) == 1)
		return (1);
	sim->number_of_coders = ft_atoi(av[1]);
	sim->time_to_burnout = ft_atoi(av[2]);
	sim->time_to_compile = ft_atoi(av[3]);
	sim->time_to_debug = ft_atoi(av[4]);
	sim->time_to_refactor = ft_atoi(av[5]);
	sim->number_of_compiles_required = ft_atoi(av[6]);
	sim->dongle_cooldown = ft_atoi(av[7]);
	if (strcmp(av[8], "fifo") == 0)
		sim->scheduler_mode = 0;
	else if (strcmp(av[8], "edf") == 0)
		sim->scheduler_mode = 1;
	else
	{
		fprintf(stderr, "Error: Expecting "
			"'edf' or 'fifo'\nGot: [ %s ]\n", av[8]);
		return (1);
	}
	return (0);
}

int	parsing_while(char **av)
{
	int		i;

	i = 1;
	while (i <= 7)
	{
		if (part_one(av, i) == 1)
			return (1);
		if (part_two(av, i) == 1)
			return (1);
		i++;
	}
	return (0);
}

int	part_one(char **av, int index)
{
	long	value;

	if ((check_number(av[index])) == 2)
	{
		printf("Error: -0 is Not Valid :)\n");
		return (1);
	}
	if (!(check_number(av[index])))
	{
		printf("Error: No Number or Negative Number.\n");
		return (1);
	}
	value = ft_atoi(av[index]);
	if (value == -1)
	{
		fprintf(stderr, "Error: Value Overflowed.\n");
		return (1);
	}
	return (0);
}

int	part_two(char **av, int index)
{
	long	value;

	value = ft_atoi(av[index]);
	if (index == 1 || index == 6)
	{
		if (index == 1)
		{
			if (value == 0)
			{
				fprintf(stderr, "Error: Coders Must Be More Than 0.\n");
				return (1);
			}
		}
		if (index == 6)
		{
			if (value == 0)
			{
				fprintf(stderr, "Error: "
					"Number of Compile Must Be More Than 0.\n");
				return (1);
			}
		}
	}
	return (0);
}
