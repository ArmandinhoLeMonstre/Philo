#include "philo.h"

void    *routine(void *arg)
{
    t_test *test = (t_test *)arg;
    pthread_mutex_t *left_fork = &test->mutex_forks[test->n];
    pthread_mutex_t *right_fork = &test->mutex_forks[(test->n + 1) % 3];
    pthread_mutex_lock(right_fork);
    pthread_mutex_lock(left_fork);
    printf("%d is taking fork\n", test->n);
    printf("%d is eating\n", test->n);
    usleep(2000);
    pthread_mutex_unlock(right_fork);
    pthread_mutex_unlock(left_fork);
    printf("%d is sleeping\n", test->n);
    //ft_usleep(2000);
}

int main(int ac, char **av)
{
    pthread_t th[3];
    int i = 0;
    t_test  test;
    test.mutex_forks = malloc(sizeof(pthread_mutex_t) * 3);
    while (i < 3)
    {
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
    for (i = 0; i < 3; i++) 
    {
        test.n = i;
        if (pthread_create(th + i, NULL, &routine, (void *)&test) != 0) {
            perror("Failed to create thread");
            return 1;
        }
        printf("Thread %d has started\n", i);
    }
    for (i = 0; i < 3; i++) 
    {
        if (pthread_join(th[i], NULL) != 0) {
            return 2;
        }
        printf("Thread %d has finished execution\n", i);
    }
    pthread_mutex_destroy(test.mutex_forks);
}