/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: outaouss <outaouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/20 01:54:46 by outaouss          #+#    #+#             */
/*   Updated: 2026/07/20 02:32:16 by outaouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int check_number(char *str)
{
    int i;

    i = 0;
    if (str[i] == '+' || str[i] == '-')
        if (str[i] == '-')
            return (0);
        i++;
    if (!str[i])
        return (0);
    while (str[i])
    {
        if (str[i] < '0' || str[i] > '9')
            return (0);
        i++;
    }
    return (1);
}
