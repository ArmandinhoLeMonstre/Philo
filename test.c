/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armitite <armitite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 08:06:17 by armitite          #+#    #+#             */
/*   Updated: 2024/12/06 18:23:45 by armitite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


void* routine(void *arg) 
{
    t_data *data = (t_data*)arg;  // Cast the argument to t_data*
    
    //printf("%d\n", data->ph->n);
    if (data->ph->n % 2 != 0)
    {
        usleep(20000);
    }
    // else
    //     data->ph->fork_right = data->forks[data->ph->n];
    // if (data->ph->n == 0)
    //     data->ph->fork_left = data->forks[data->ph_nbr - 1];
    // else
    //     data->ph->fork_left = data->forks[data->ph->n - 1];
    while (data->meals_nbr < 1500000) 
    {
        pthread_mutex_lock(&data->mutex);
        // printf("Philo %d is taking right fork %d\n", data->ph->n, data->ph->fork_right);
        // printf("Philo %d is taking left fork %d\n", data->ph->n, data->ph->fork_left);
        // printf("Philo %d is eating\n", data->ph->n);
        data->meals_nbr++;
        usleep(2000);
        // printf("Philo %d is dropping right fork %d\n", data->ph->n, data->ph->fork_right);
        // printf("Philo %d is dropping left fork %d\n", data->ph->n, data->ph->fork_left);
        pthread_mutex_unlock(&data->mutex);
        printf("Philo %d is sleeping\n", data->ph->n);
        usleep(2000);
    }
    return NULL;
}

int start_philo(t_data *data)
{
    pthread_t th[data->ph_nbr];
    t_philo p;
    int i;

    data->mails = 0;
    data->lock = 0;
    data->death = 0;
    i = 0;

    p.data->mutex_forks = malloc(sizeof(pthread_mutex_t) * data->ph_nbr);
    while (i < data->ph_nbr)
    {
        if (pthread_mutex_init(&data->mutex_forks[i], NULL) != 0)
        {
            perror("Mutex initialization failed");
            // Clean up already initialized mutexes
            while (i > 0)
            {
                i--;
                pthread_mutex_destroy(&data->mutex_forks[i]);
            }
            free(data->mutex_forks);
            free(data);
            return (1); // Handle initialization failure
        }
        i++;
    }
    printf("ici ?\n");
    i = 0;
    while (i < data->ph_nbr) 
    {
        data->ph->n = i;
        if (data->ph->n == data->ph_nbr - 1)
            data->ph->fork_right = data->forks[0];
        else
            data->ph->fork_right = data->forks[data->ph->n];
        if (data->ph->n == 0)
            data->ph->fork_left = data->forks[data->ph_nbr - 1];
        else
            data->ph->fork_left = data->forks[data->ph->n - 1];
        if (pthread_create(th + i, NULL, &routine, (void *)data) != 0) {
            perror("Failed to create thread");
            return 1;
        }
        printf("Thread %d has started\n", i);
        i++;
    }
    i = 0;
    while (i < data->ph_nbr) 
    {
        if (pthread_join(th[i], NULL) != 0) {
            return 2;
        }
        printf("Thread %d has finished execution\n", i);
    }

    pthread_mutex_destroy(&data->mutex);

    // Print the final mails count
    printf("Number of mails: %d\n", data->meals_nbr);
    free(data->ph);
    free(data->forks);
    return 0;
}

int stock_args(t_data *data, int ac, char **av)
{
    data->ph_nbr= ft_atoi(av[1]);
    data->starving_time = ft_atoi(av[2]);
    data->eating_time = ft_atoi(av[3]);
    data->sleeping_time = ft_atoi(av[4]);
    if (ac == 6)
        data->meals_nbr = ft_atoi(av[5]);
    else
        data->meals_nbr = -1;
}

int main(int ac, char **av) 
{
    t_data data;
    if (ac == 6 || ac == 5)
        stock_args(&data, ac, av);
    else
        return (printf("args"), 2);
    printf("%d\n", data.ph_nbr);
    printf("%d\n", data.starving_time);
    printf("%d\n", data.eating_time);
    printf("%d\n", data.sleeping_time);
    //ft_usleep(data.sleeping_time);
    printf("%d\n", data.meals_nbr);
    start_philo(&data);
    return (0);
}
