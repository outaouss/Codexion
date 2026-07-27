/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dongles.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: splinta <splinta@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/24 17:31:26 by outaouss          #+#    #+#             */
/*   Updated: 2026/07/27 01:51:45 by splinta          ###   ########.fr       */
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

// int	request_dongles(t_coder *coder)
// {
// 	while (check_stop_flag(coder->data) == 0)
// 	{
// 		pthread_mutex_lock(&coder->left->d_mutex);
// 		if (is_dongle_ready(coder->left, coder))
// 		{
// 			pthread_mutex_lock(&coder->right->d_mutex);
// 			if (is_dongle_ready(coder->right, coder))
// 			{
// 				coder->left->in_process = 1;
// 				coder->right->in_process = 1;
// 				pop(&coder->left->heap);
// 				pop(&coder->right->heap);
// 				pthread_mutex_unlock(&coder->right->d_mutex);
// 				pthread_mutex_unlock(&coder->left->d_mutex);
// 				return (1);
// 			}
// 			pthread_mutex_unlock(&coder->right->d_mutex);
// 		}
// 		pthread_mutex_unlock(&coder->left->d_mutex);
// 		usleep(300);
// 	}
// 	return (0);
// }

int request_dongles(t_coder *coder)
{
    while (check_stop_flag(coder->data) == 0)
    {
        /* Always lock both dongle mutexes to check atomic availability */
        pthread_mutex_lock(&coder->left->d_mutex);
        pthread_mutex_lock(&coder->right->d_mutex);

        if (is_dongle_ready(coder->left, coder) && is_dongle_ready(coder->right, coder))
        {
            coder->left->in_process = 1;
            coder->right->in_process = 1;
            pop(&coder->left->heap);
            pop(&coder->right->heap);
            pthread_mutex_unlock(&coder->right->d_mutex);
            pthread_mutex_unlock(&coder->left->d_mutex);
            return (1);
        }

        pthread_mutex_unlock(&coder->right->d_mutex);
        pthread_mutex_unlock(&coder->left->d_mutex);
        usleep(100);
    }
    return (0);
}

// void	take_dongles(t_coder *coder)
// {
// 	coder->request_time = get_time();
// 	coder->deadline = coder->last_compile_start + coder->data->time_to_burnout;

// 	if (coder->data->number_of_coders == 1)
// 	{
// 		pthread_mutex_lock(&coder->left->d_mutex);
// 		print_action(coder, "has taken a dongle");
// 		while (check_stop_flag(coder->data) == 0)
// 			usleep(100);
// 		pthread_mutex_unlock(&coder->left->d_mutex);
// 		return ;
// 	}
	
// 	pthread_mutex_lock(&coder->left->d_mutex);
// 	push(&coder->left->heap, coder);
// 	pthread_mutex_unlock(&coder->left->d_mutex);
	
// 	pthread_mutex_lock(&coder->right->d_mutex);
// 	push(&coder->right->heap, coder);
// 	pthread_mutex_unlock(&coder->right->d_mutex);
	
// 	if (request_dongles(coder) == 1)
// 	{
// 		print_action(coder, "has taken a dongle");
// 		print_action(coder, "has taken a dongle");
// 	}
// }

void    take_dongles(t_coder *coder)
{
    /* 1. Safely record request time and deadline under c_mutex */
    pthread_mutex_lock(&coder->c_mutex);
    coder->request_time = get_time();
    coder->deadline = coder->last_compile_start + coder->data->time_to_burnout;
    pthread_mutex_unlock(&coder->c_mutex);

    /* Edge case: 1 coder (only 1 dongle exists in total) */
    if (coder->data->number_of_coders == 1)
    {
        pthread_mutex_lock(&coder->left->d_mutex);
        print_action(coder, "has taken a dongle");
        while (check_stop_flag(coder->data) == 0)
            usleep(100);
        pthread_mutex_unlock(&coder->left->d_mutex);
        return ;
    }

    /* 2. Register presence in BOTH dongle heaps */
    pthread_mutex_lock(&coder->left->d_mutex);
    push(&coder->left->heap, coder);
    pthread_mutex_unlock(&coder->left->d_mutex);

    pthread_mutex_lock(&coder->right->d_mutex);
    push(&coder->right->heap, coder);
    pthread_mutex_unlock(&coder->right->d_mutex);

    /* 3. Spin/Wait until BOTH dongles grant priority to this coder */
    while (check_stop_flag(coder->data) == 0)
    {
        if (request_dongles(coder) == 1)
        {
            print_action(coder, "has taken a dongle");
            print_action(coder, "has taken a dongle");
            break ;
        }
        usleep(100); /* Prevent 100% CPU usage while waiting */
    }
}

void release_dongles(t_coder *coder)
{
	long	release_time;

	release_time = get_time();
	
	pthread_mutex_lock(&coder->left->d_mutex);
	coder->left->in_process = 0;
	coder->left->available_at = release_time + coder->data->dongle_cooldown;
	pthread_mutex_unlock(&coder->left->d_mutex);
	
	pthread_mutex_lock(&coder->right->d_mutex);
	coder->right->in_process = 0;
	coder->right->available_at = release_time + coder->data->dongle_cooldown;
	pthread_mutex_unlock(&coder->right->d_mutex);
}

// void take_dongles(t_coder *coder)
// {
//     pthread_mutex_lock(&coder->left->d_mutex);
//     print_action(coder, "has taken a dongle");
    
//     pthread_mutex_lock(&coder->right->d_mutex);
//     print_action(coder, "has taken a dongle");
// }

void do_compile(t_coder *coder)
{
    pthread_mutex_lock(&coder->c_mutex);
    coder->last_compile_start = get_time();
    // coder->compile_count++;
    pthread_mutex_unlock(&coder->c_mutex);

    print_action(coder, "is compiling");
    c_sleep(coder->data->time_to_compile);
}

// void release_dongles(t_coder *coder)
// {
//     pthread_mutex_unlock(&coder->left->d_mutex);
//     pthread_mutex_unlock(&coder->right->d_mutex);
// }

void do_rest_and_refactor(t_coder *coder)
{
    print_action(coder, "is debugging");
    c_sleep(coder->data->time_to_debug);

    print_action(coder, "is refactoring");
    c_sleep(coder->data->time_to_refactor);    
}
