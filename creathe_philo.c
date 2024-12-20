#include "philo.h"

void	eat(t_philo *p, pthread_mutex_t *left_fork, pthread_mutex_t *right_fork)
{
	pthread_mutex_lock(right_fork);
	pthread_mutex_lock(left_fork);
    pthread_mutex_lock(p->data->mutex_death);
    if (p->data->death == 1)
    {
        pthread_mutex_unlock(p->data->mutex_death);
        pthread_mutex_unlock(right_fork);
        pthread_mutex_unlock(left_fork);
        return;
    }
    if (p->data->meals_eaten == (p->data->meals_nbr * p->data->ph_nbr))
    {
        pthread_mutex_unlock(p->data->mutex_death);
        pthread_mutex_unlock(right_fork);
        pthread_mutex_unlock(left_fork);
        return ;
    }
    pthread_mutex_unlock(p->data->mutex_death);
	printf("%ld %d is taking fork\n", time_now() - p->time, p->n);
    printf("%ld %d is taking fork\n", time_now() - p->time, p->n);
	printf("%ld %d is eating\n", time_now() - p->time, p->n);
    pthread_mutex_lock(p->data->mutex_meals);
    if (p->data->meals_eaten == (p->data->meals_nbr * p->data->ph_nbr))
    {
        pthread_mutex_unlock(p->data->mutex_meals);
        pthread_mutex_unlock(right_fork);
        pthread_mutex_unlock(left_fork);
        return ;
    }
    if (p->data->meals_nbr != -1)
        p->data->meals_eaten++;
    if (p->data->meals_eaten == (p->data->meals_nbr * p->data->ph_nbr))
    {
        pthread_mutex_unlock(p->data->mutex_meals);
        pthread_mutex_unlock(right_fork);
        pthread_mutex_unlock(left_fork);
        return ;
    }
    pthread_mutex_unlock(p->data->mutex_meals);
    p->t_last_meal = time_now();
	ft_usleep(p->data->eating_time);
	pthread_mutex_unlock(right_fork);
    //printf("%ld %d dropped fork\n", time_now() - p->time, p->n);
	pthread_mutex_unlock(left_fork);
    //printf("%ld %d dropped fork\n", time_now() - p->time, p->n);
}

void    *monitoring(void *arg)
{
    t_philo **p = (t_philo **) arg;
    t_test  *data;
    int i;

    data = malloc(sizeof(t_test) * 1);
    data = p[0]->data;
    ft_usleep(150);
    while (1)
    {
        i = 0;
        while (i < data->ph_nbr)
        {
            pthread_mutex_lock(data->mutex_death);
            if ((time_now() - p[i]->t_last_meal) > data->starving_time)
            {
                data->death = 1;
                printf("%ld %d is dead\n", (time_now() - p[i]->time), p[i]->n);
                pthread_mutex_unlock(data->mutex_death);
                return NULL;
            }
            if (data->meals_eaten == (data->meals_nbr * data->ph_nbr))
            {
                printf("%d meals have been eaten\n", data->meals_eaten);
                pthread_mutex_unlock(data->mutex_death);
                return NULL;
            }
            pthread_mutex_unlock(data->mutex_death);
            i++;
        }
    }
    //free(data);
}

void    *routine(void *arg)
{
    t_philo *p = (t_philo *)arg;
    p->t_last_meal = time_now();
	while (p->data->check != 1)
		continue ;
	p->death_p = 0;
    pthread_mutex_t *left_fork = &p->data->mutex_forks[p->n];
    pthread_mutex_t *right_fork = &p->data->mutex_forks[(p->n % p->data->ph_nbr) + 1];
    p->time = time_now();
    if (p->n % 2 == 0)
	    ft_usleep(150);
    //printf("%d\n", p->data->starving_time);
	while (1)
	{
        pthread_mutex_lock(p->data->mutex_death);
		if (p->data->death == 1)
        {
            pthread_mutex_unlock(p->data->mutex_death);
			break ;
        }
		if (p->data->meals_eaten == (p->data->meals_nbr * p->data->ph_nbr))
        {
            pthread_mutex_unlock(p->data->mutex_death);
			break ;
        }
        pthread_mutex_unlock(p->data->mutex_death);
		eat(p, left_fork, right_fork);
        pthread_mutex_lock(p->data->mutex_death);
		if (p->data->death == 1)
        {
            pthread_mutex_unlock(p->data->mutex_death);
			break ;
        }
        if (p->data->meals_eaten == (p->data->meals_nbr * p->data->ph_nbr))
        {
            pthread_mutex_unlock(p->data->mutex_death);
			break ;
        }
        pthread_mutex_unlock(p->data->mutex_death);
		printf("%ld %d is sleeping\n", time_now() - p->time, p->n);
		ft_usleep(p->data->sleeping_time);
        pthread_mutex_lock(p->data->mutex_death);
		if (p->data->death == 1)
        {
            pthread_mutex_unlock(p->data->mutex_death);
			break ;
        }
        if (p->data->meals_eaten == (p->data->meals_nbr * p->data->ph_nbr))
        {
            pthread_mutex_unlock(p->data->mutex_death);
			break ;
        }
        pthread_mutex_unlock(p->data->mutex_death);
        printf("%ld %d is thinking\n",time_now() - p->time, p->n);
	}
    return NULL;
}

int create_philo(t_philo **philo, t_test *test)
{
    int i;

    pthread_t th[test->ph_nbr];
    pthread_t monitor;
    for (i = 0; i < test->ph_nbr; i++) 
    {
        //test->n = i;
        
        if (pthread_create(th + i, NULL, &routine, (void *)philo[i]) != 0) {
            perror("Failed to create thread");
            return 1;
        }
        //printf("Thread %d has started\n", i);
    }
    if (pthread_create(&monitor, NULL, &monitoring, (void *)philo) != 0) 
    {
        perror("Failed to create thread");
        return 1;
    }
    for (i = 0; i < test->ph_nbr; i++) 
    {
        if (pthread_join(th[i], NULL) != 0) {
            return 3;
        }
        printf("Thread %d has finished execution\n", i);
    }
    if (pthread_join(monitor, NULL) != 0) 
    {
        return 2;
    }
    for (i = 0; i < test->ph_nbr; i++)
        pthread_mutex_destroy(&test->mutex_forks[i]);
	pthread_mutex_destroy(test->mutex_death);
    return (0);
}