/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: splinta <splinta@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/20 01:53:04 by outaouss          #+#    #+#             */
/*   Updated: 2026/07/27 01:06:31 by splinta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODEXION_H
# define CODEXION_H

#include <stdio.h>
#include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_sim t_sim;

typedef struct s_heap {
    void *array[2];
    int count;
    int capacity;
} t_heap;

typedef struct s_dongle
{
    long            available_at;
    int             in_process;
    pthread_mutex_t d_mutex;
    t_heap          heap;
}   t_dongle;

typedef struct s_coder
{
    int             id;
    long            last_compile_start;
    int             compile_count;
    pthread_t       thread;
    t_dongle        *left;
    t_dongle        *right;
    t_sim          *data;
    pthread_mutex_t c_mutex;
    size_t request_time;
    size_t deadline;
}   t_coder;

typedef struct s_sim
{
    long start_time;

    int number_of_coders;
    int time_to_burnout;
    int time_to_compile;
    int time_to_debug;
    int time_to_refactor;
    int number_of_compiles_required;
    int dongle_cooldown;
    int stop_flag;

    int scheduler_mode;

    pthread_mutex_t print_mutex;
    t_dongle *dongles;
    t_coder         *coders;
    pthread_mutex_t stop_mutex;

    pthread_mutex_t start_mutex;
    pthread_cond_t start_cond;

    int simulation_started;

}   t_sim;


int check_number(char *str);
int parsing(char **av, t_sim *sim);
long	ft_atoi(char *str);
// int init_heaps(t_sim *sim);
// int init_simulation(t_sim *sim);
void swap_nodes(t_coder **a, t_coder **b);
void push(t_heap *heap, t_coder *coder);
t_coder *pop(t_heap *heap);
void bubble_up(t_heap *heap, int index);
void bubble_down(t_heap *heap, int index);
void c_sleep(size_t duration, t_sim *sim);
size_t  get_time(void);
// int start_simulation(t_sim *sim);
// void *coder_routine(void *arg);
void take_dongles(t_coder *coder);
void do_compile(t_coder *coder);
void release_dongles(t_coder *coder);
void do_rest_and_refactor(t_coder *coder);
void print_action(t_coder *coder, char *status);
int check_stop_flag(t_sim *sim);
int check_burnout(t_sim *sim);
int check_all_compiled(t_sim *sim);
void *monitor_thread(void *arg);
int is_higher_priority(t_coder *a, t_coder *b);
int	request_dongles(t_coder *coder);
int	is_dongle_ready(t_dongle *dongle, t_coder *coder);
void free_all(t_sim *sim);
// void destroy_dongles_mutex(t_sim *sim);
// void destroy_coders_mutex(t_sim *sim);
// void destroy_sim_mutex(t_sim *sim);
void	destroy_all_mutexes(t_sim *sim);
void	dongle_take_helper(t_coder *coder);
int	part_two(char **av, int index);
int	part_one(char **av, int index);
int	parsing_while(char **av);

// Simulation

int abort_simulation(t_sim *sim, int count);
int setup_simulation(t_sim *sim, pthread_t *monitor);
int start_simulation(t_sim *sim);
void coder_prepare(t_coder *coder);
void coder_compile_loop(t_coder *coder);
void *coder_routine(void *arg);
void	init_last_compile(t_sim *sim);

// init

void	destroy_coder_mutexes(t_sim *sim, int count);
int	init_coder(t_sim *sim, int i);
int	init_coders(t_sim *sim);
void	init_sync_primitives(t_sim *sim);
int	init_simulation(t_sim *sim);
void	init_heaps(t_sim *sim);
int	alloc_simulation(t_sim *sim);
void	destroy_dongle_mutexes(t_sim *sim, int count);
int	init_dongles(t_sim *sim);

#endif