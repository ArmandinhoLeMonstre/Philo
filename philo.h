/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armitite <armitite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 08:59:01 by armitite          #+#    #+#             */
/*   Updated: 2024/12/13 17:35:35 by armitite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H


#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>
# include "Libft/libft.h"


// typedef struct s_data
// {
//     int mails;
//     int lock;
//     int ph_nbr;
//     int starving_time;
//     int eating_time;
//     int sleeping_time;
//     int meals_nbr;
//     int death;
//     pthread_mutex_t *mutex_forks;

// } t_data;

typedef struct s_test
{
    int n;
    int i;
    int ph_nbr;
    int starving_time;
    int eating_time;
    int sleeping_time;
    int meals_nbr;
    int death;
    int check;
    int meals_eaten;
    pthread_mutex_t *mutex_death;
    pthread_mutex_t *mutex_print;
    pthread_mutex_t *mutex_forks;
    pthread_mutex_t *mutex_meals;

} t_test;

typedef struct s_philo
{
    int n;
    int death_p;
    int fork_left;
    int fork_right;
    long int time;
    long int t_last_meal;
    t_test *data;
    //pthread_t th;

} t_philo;


int	ft_usleep(long int time);
int	ft_atoi(const char *str);
long int	time_now(void);
int create_philo(t_philo **philo, t_test *test);

#endif
