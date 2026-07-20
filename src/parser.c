/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: outaouss <outaouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/20 01:52:47 by outaouss          #+#    #+#             */
/*   Updated: 2026/07/20 02:35:43 by outaouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int main(int argc, char **argv)
{
    int i = 1;

    if (argc == 9)
    {
        while(i <= 7)
        {
            if (!(check_number(argv[i])))
            {
                printf("Error\n");
                return 0;
            }
            i++;
        }
        if (strcmp(argv[8], "fifo") != 0 && strcmp(argv[8], "edf") != 0)
        {
            fprintf(stderr, "Error: Expecting 'edf' or 'fifo'\nGot: [ %s ]\n", argv[8]);
            return (0);
        }
    }
    else
    {
        fprintf(stderr, "Error: Inputs Must Be 8\nGot: [ %d ]\n", argc - 1);
        return 0;
    }
}