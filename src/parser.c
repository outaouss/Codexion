/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: outaouss <outaouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/20 01:52:47 by outaouss          #+#    #+#             */
/*   Updated: 2026/07/21 20:09:47 by outaouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int parsing(char **av, t_sim *sim)
{

    int i = 1;
    long value;

    while(i <= 7)
    {
        if (!(check_number(av[i])))
        {
            printf("Error: No Number or Negative Number.\n");
            return (0);
        }
        value = ft_atoi(av[i]);

        if (value == -1)
        {
            fprintf(stderr, "Error: Value Overflowed.\n");
            return (0);
        }
        if (i == 1)
        {
            if (value == 0)
            {
                fprintf(stderr, "Error: Coders Must Be More Than 0.\n");
                return (0);
            }
        }
        i++;
    }
    sim->number_of_coders = ft_atoi(av[1]);
    sim->time_to_burnout = ft_atoi(av[2]);
    sim->time_to_compile = ft_atoi(av[3]);
    sim->time_to_debug = ft_atoi(av[4]);
    sim->time_to_refactor = ft_atoi(av[5]);
    sim->number_of_compiles_required = ft_atoi(av[6]);
    sim->dongle_cooldown = ft_atoi(av[7]);

    if (strcmp(av[i], "fifo") == 0)
        sim->scheduler_mode = 0;
    else if (strcmp(av[i], "edf") == 0)
        sim->scheduler_mode = 1;
    else
    {
        fprintf(stderr, "Error: Expecting 'edf' or 'fifo'\nGot: [ %s ]\n", av[i]);
        return (0);
    }
    return (1);
}
