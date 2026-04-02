#include "philo.h"

int	stop_routine(t_data *data)
{
    int	stop;

    pthread_mutex_lock(&data->lock_mutex);
    stop = data->stop;
    pthread_mutex_unlock(&data->lock_mutex);
    return (stop);
}

void	set_stop(t_data *data)
{
    pthread_mutex_lock(&data->lock_mutex);
    data->stop = 1;
    pthread_mutex_unlock(&data->lock_mutex);
}

void	smart_sleep(t_data *data, long long duration_ms)
{
    long long	start;

    start = start_time();
    while (!stop_routine(data) && end_time(start) < duration_ms)
        usleep(500);
}



int	all_full_eat(t_data *data)
{
    int			i;
    long long	target;

    if (data->nb_eat_before_stop == -1)
        return (0);
    target = data->nb_eat_before_stop;
    pthread_mutex_lock(&data->lock_mutex);
    i = 0;
    while (i < data->philo_nb)
    {
        if (data->philo[i].nb_eat < target)
        {
            pthread_mutex_unlock(&data->lock_mutex);
            return (0);
        }
        i++;
    }
    pthread_mutex_unlock(&data->lock_mutex);
    return (1);
}