#include "philo.h"

void	eat(t_philo *p, pthread_mutex_t *left_fork, pthread_mutex_t *right_fork)
{
	pthread_mutex_lock(right_fork);
	pthread_mutex_lock(left_fork);
	printf("%d is taking fork\n", p->n);
	printf("%d is eating\n", p->n);
    p->t_last_meal = time_now();
	ft_usleep(p->data->eating_time);
	pthread_mutex_unlock(right_fork);
	pthread_mutex_unlock(left_fork);
}

void    *routine(void *arg)
{
    t_philo *p = (t_philo *)arg;
    // if (p->n % 2 == 0)
    //     ft_usleep(150);
	while (p->data->check != 1)
		continue ;
	ft_usleep(150);
	p->death_p = 0;
    pthread_mutex_t *left_fork = &p->data->mutex_forks[p->n];
    pthread_mutex_t *right_fork = &p->data->mutex_forks[(p->n + 1) % 3];
    p->t_last_meal = time_now();
	while (p->data->death == 0)
	{
		if (p->data->death == 1)
			break ;
		pthread_mutex_lock(p->data->mutex_death);
		if ((time_now() - p->t_last_meal) < p->data->starving_time)
		{
            printf("ici ?");
			p->death_p = 1;
			printf("%d is dead\n", p->n);
			//exit(1);
		}
		pthread_mutex_unlock(p->data->mutex_death);
		//p->t_last_meal = time_now();
		eat(p, left_fork, right_fork);
		printf("%d is sleeping\n", p->n);
		ft_usleep(p->data->sleeping_time);
	}
}

int create_philo(t_philo **philo, t_test *test)
{
    int i;

    pthread_t th[test->ph_nbr];
    for (i = 0; i < test->ph_nbr; i++) 
    {
        test->n = i;
        if (pthread_create(th + i, NULL, &routine, (void *)philo[i]) != 0) {
            perror("Failed to create thread");
            return 1;
        }
        printf("Thread %d has started\n", i);
    }
    // while(1)
    // {
    //     i = 0;
    //     while (i < test->ph_nbr)
    //     {
    //         if (philo[i]->death_p == 1)
    //         {
    //             //pthread_mutex_lock(philo[i]->data->mutex_death);
    //             test->death = 1;
    //             //pthread_mutex_unlock(philo[i]->data->mutex_death);
    //             //exit(1);
    //             break ;
    //         }
    //         i++;
    //     }
    //     ft_usleep(1000);
    // }
    //pthread_mutex_unlock(philo[i]->data->mutex_death);
    for (i = 0; i < test->ph_nbr; i++) 
    {
        if (pthread_join(th[i], NULL) != 0) {
            return 2;
        }
        printf("Thread %d has finished execution\n", i);
    }
}