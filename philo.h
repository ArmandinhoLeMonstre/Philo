/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armitite <armitite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 08:59:01 by armitite          #+#    #+#             */
/*   Updated: 2024/12/06 15:57:07 by armitite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H


#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
# include "Libft/libft.h"

typedef struct s_philo
{
    int n;
    int fork_left;
    int fork_right;
    pthread_mutex_t mutex_print;

} t_philo;

typedef struct s_data
{
    int mails;
    int lock;
    int ph_nbr;
    int starving_time;
    int eating_time;
    int sleeping_time;
    int meals_nbr;
    int *forks;
    int death;
    t_philo *ph;
    pthread_mutex_t mutex;
    pthread_mutex_t mutex_fork;
    //pthread_mutex_t mutex_print;

} t_data;


#endif
