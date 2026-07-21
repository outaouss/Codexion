/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: outaouss <outaouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/20 01:52:44 by outaouss          #+#    #+#             */
/*   Updated: 2026/07/21 20:10:47 by outaouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int main(int argc, char **argv)
{
    t_sim sim;

    if (argc == 9)
    {
        if (parsing(argv, &sim) == 0)
            return (0);
    }
    else
    {
        fprintf(stderr, "Error: Inputs Must Be 8\nGot: [ %d ]\n", argc - 1);
        return (0);
    }
    printf("Coders: %ld, Scheduler: %d\n", sim.number_of_coders, sim.scheduler_mode);
}
