/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: outaouss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/24 17:42:41 by outaouss          #+#    #+#             */
/*   Updated: 2026/07/24 17:42:42 by outaouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "codexion.h"

void print_action(t_coder *coder, char *status)
{
    size_t timestamp;

    timestamp = get_time() - coder->data->start_time;
    pthread_mutex_lock(&coder->data->print_mutex);

    printf("%ld %d %s\n", timestamp, coder->id, status);

    pthread_mutex_unlock(&coder->data->print_mutex);
}
