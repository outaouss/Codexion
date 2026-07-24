/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dongles.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: outaouss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/24 17:31:26 by outaouss          #+#    #+#             */
/*   Updated: 2026/07/24 17:31:27 by outaouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "codexion.h"

void take_dongles(t_coder *coder)
{
    pthread_mutex_lock(&coder->left->d_mutex);
    print_action(coder, "has taken a dongle");
    
    pthread_mutex_lock(&coder->right->d_mutex);
    print_action(coder, "has taken a dongle");
}

void do_compile(t_coder *coder)
{
    pthread_mutex_lock(&coder->c_mutex);
    coder->last_compile_start = get_time();
    coder->compile_count++;
    pthread_mutex_unlock(&coder->c_mutex);

    print_action(coder, "is compiling");
    c_sleep(coder->data->time_to_compile);
}

void release_dongles(t_coder *coder)
{
    pthread_mutex_unlock(&coder->left->d_mutex);
    pthread_mutex_unlock(&coder->right->d_mutex);
}

void do_rest_and_refactor(t_coder *coder)
{
    print_action(coder, "is debugging");
    c_sleep(coder->data->time_to_debug);

    print_action(coder, "is refactoring");
    c_sleep(coder->data->time_to_refactor);    
}