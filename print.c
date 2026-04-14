#include "philo.h"

void	print_action(t_data *data, int id, const char *msg)
{
    int			stop;
    long long	timestamp;

    pthread_mutex_lock(&data->state_lock);
    stop = data->stop;
    pthread_mutex_unlock(&data->state_lock);
    if (stop)
        return ;
    pthread_mutex_lock(&data->print);
    pthread_mutex_lock(&data->state_lock);
    if (!data->stop)
    {
        timestamp = end_time(data->time_start);
        printf("%lld %d %s\n", timestamp, id, msg);
    }
    pthread_mutex_unlock(&data->state_lock);
    pthread_mutex_unlock(&data->print);
}

void	print_death(t_data *data, int id)
{
    long long	timestamp;

    pthread_mutex_lock(&data->print);
    timestamp = end_time(data->time_start);
    printf("%lld %d died\n", timestamp, id);
    pthread_mutex_unlock(&data->print);
}
