#include "philo.h"

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
    data->death = 0;
	data->check = 0;
	data->mutex_death = malloc(sizeof(pthread_mutex_t) * 1);
    data->mutex_print = malloc(sizeof(pthread_mutex_t) * 1);
    data->mutex_meals = malloc(sizeof(pthread_mutex_t) * 1);
    // Proteger Malloc
}

int init_philo(t_test *data)
{
    int i;

    i = 0;
    t_philo **philo;
	if (pthread_mutex_init(data->mutex_death, (void *)&data) != 0)
        exit(1);
    if (pthread_mutex_init(data->mutex_meals, (void *)&data) != 0)
        exit(1);
	if (pthread_mutex_init(data->mutex_print, (void *)&data) != 0)
        exit(1);
    philo = malloc(sizeof(t_philo *) * data->ph_nbr);
    while (i < data->ph_nbr)
    {
        philo[i] = malloc(sizeof(t_philo) * data->ph_nbr);
        philo[i]->data = malloc (sizeof(t_test));
        philo[i]->data = data;
        philo[i]->n = i + 1;
        i++;
    }
    i = 0;
    data->mutex_forks = malloc(sizeof(pthread_mutex_t) * (data->ph_nbr + 1));
    while (i < data->ph_nbr)
    {
        //data->i = i;
		if (i == (data->ph_nbr - 1))
			data->check = 1;
        if (pthread_mutex_init(&data->mutex_forks[i + 1], (void *)&data) != 0)
        {
            perror("Mutex initialization failed");
            while (i > 0)
            {
                i--;
                pthread_mutex_destroy(&data->mutex_forks[i + 1]);
            }
            free(data->mutex_forks);
            return (1);
        }
        i++;
    }
    create_philo(philo, data);
}

int main(int ac, char **av)
{
    int i = 0;
    t_test  test;
    t_philo **philo;
    if (ac == 6 || ac == 5)
        stock_args(&test, ac, av);
    else
        return (printf("Error args\n"), 0);
    //init_philo(&test);
	if (pthread_mutex_init(test.mutex_death, (void *)&test) != 0)
        exit(1);
    philo = malloc(sizeof(t_philo *) * test.ph_nbr);
    while (i < test.ph_nbr)
    {
        philo[i] = malloc(sizeof(t_philo) * test.ph_nbr);
        philo[i]->data = malloc (sizeof(t_test));
        philo[i]->data = &test;
        philo[i]->n = i + 1;
        i++;
    }
    i = 0;
    test.mutex_forks = malloc(sizeof(pthread_mutex_t) * (test.ph_nbr + 1));
    while (i < test.ph_nbr)
    {
        test.i = i;
		if (i == (test.ph_nbr - 1))
			test.check = 1;
        if (pthread_mutex_init(&test.mutex_forks[i + 1], (void *)&test) != 0)
        {
            perror("Mutex initialization failed");
            while (i > 0)
            {
                i--;
                pthread_mutex_destroy(&test.mutex_forks[i + 1]);
            }
            free(test.mutex_forks);
            return (1);
        }
        i++;
    }
	i = 0;
    printf("le i : %d\n", test.i);
	create_philo(philo, &test);
// 	while (i > 0)
// 	{
// 		i--;
// 		pthread_mutex_destroy(&test.mutex_forks[i]);
// 	}
//     pthread_mutex_destroy(test.mutex_forks);
// 	pthread_mutex_destroy(test.mutex_death);
}