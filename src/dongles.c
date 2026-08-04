/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dongles.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: outaouss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 06:20:54 by outaouss          #+#    #+#             */
/*   Updated: 2026/08/04 06:20:56 by outaouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	request_dongles(t_coder *coder)
{
	while (check_stop_flag(coder->data) == 0)
	{
		pthread_mutex_lock(&coder->left->d_mutex);
		pthread_mutex_lock(&coder->right->d_mutex);
		if (is_dongle_ready(coder->left, coder)
			&& is_dongle_ready(coder->right, coder))
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

void	take_dongles(t_coder *coder)
{
	pthread_mutex_lock(&coder->c_mutex);
	coder->request_time = get_time();
	coder->deadline = coder->last_compile_start + coder->data->time_to_burnout;
	pthread_mutex_unlock(&coder->c_mutex);
	if (coder->data->number_of_coders == 1)
	{
		pthread_mutex_lock(&coder->left->d_mutex);
		print_action(coder, "has taken a dongle");
		while (check_stop_flag(coder->data) == 0)
			usleep(100);
		pthread_mutex_unlock(&coder->left->d_mutex);
		return ;
	}
	pthread_mutex_lock(&coder->left->d_mutex);
	push(&coder->left->heap, coder);
	pthread_mutex_unlock(&coder->left->d_mutex);
	pthread_mutex_lock(&coder->right->d_mutex);
	push(&coder->right->heap, coder);
	pthread_mutex_unlock(&coder->right->d_mutex);
	dongle_take_helper(coder);
}

void	release_dongles(t_coder *coder)
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

void	do_compile(t_coder *coder)
{
	pthread_mutex_lock(&coder->c_mutex);
	coder->last_compile_start = get_time();
	pthread_mutex_unlock(&coder->c_mutex);
	print_action(coder, "is compiling");
	c_sleep(coder->data->time_to_compile, coder->data);
}

void	do_rest_and_refactor(t_coder *coder)
{
	print_action(coder, "is debugging");
	c_sleep(coder->data->time_to_debug, coder->data);
	print_action(coder, "is refactoring");
	c_sleep(coder->data->time_to_refactor, coder->data);
}
