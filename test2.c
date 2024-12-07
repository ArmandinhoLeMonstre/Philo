#include "philo.h"

void    *routine(void *arg)
{
    t_philo *p = (t_philo *)arg;
    if (p->n % 2 == 0)
        ft_usleep(150);
    if (p->n == 0)
        p->data->n = 13;
    pthread_mutex_t *left_fork = &p->data->mutex_forks[p->n];
    pthread_mutex_t *right_fork = &p->data->mutex_forks[(p->n + 1) % 3];
    pthread_mutex_lock(right_fork);
    pthread_mutex_lock(left_fork);
    printf("%d is taking fork\n", p->n);
    printf("%d is eating\n", p->n);
    ft_usleep(p->data->eating_time);
    pthread_mutex_unlock(right_fork);
    pthread_mutex_unlock(left_fork);
    printf("%d is sleeping\n", p->n);
    printf("%d\n", p->data->n);
    ft_usleep(p->data->sleeping_time);
}

int stock_args(t_test *data, int ac, char **av)
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
    int i = 0;
    t_test  test;
    t_philo **philo;
    if (ac == 6 || ac == 5)
        stock_args(&test, ac, av);
    pthread_t th[test.ph_nbr];
    philo = malloc(sizeof(t_philo *) * test.ph_nbr);
    while (i < test.ph_nbr)
    {
        philo[i] = malloc(sizeof(t_philo) * test.ph_nbr);
        philo[i]->data = malloc (sizeof(t_test));
        philo[i]->data = &test;
        philo[i]->n = i;
        i++;
    }
    i = 0;
    test.mutex_forks = malloc(sizeof(pthread_mutex_t) * test.ph_nbr);
    while (i < test.ph_nbr)
    {
        test.i = i;
        if (pthread_mutex_init(&test.mutex_forks[i], (void *)&test) != 0)
        {
            perror("Mutex initialization failed");
            while (i > 0)
            {
                i--;
                pthread_mutex_destroy(&test.mutex_forks[i]);
            }
            free(test.mutex_forks);
            return (1);
        }
        i++;
    }
    for (i = 0; i < test.ph_nbr; i++) 
    {
        test.n = i;
        if (pthread_create(th + i, NULL, &routine, (void *)philo[i]) != 0) {
            perror("Failed to create thread");
            return 1;
        }
        printf("Thread %d has started\n", i);
    }
    for (i = 0; i < test.ph_nbr; i++) 
    {
        if (pthread_join(th[i], NULL) != 0) {
            return 2;
        }
        printf("Thread %d has finished execution\n", i);
    }
    pthread_mutex_destroy(test.mutex_forks);
}