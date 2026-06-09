#include "philo.h"

void	print_action(t_data *data, int id, const char *msg)
{
	long long	time;

	pthread_mutex_lock(&data->print);
	pthread_mutex_lock(&data->state_lock);
	if (!data->stop)
	{
		time = end_time(data->time_start);
		printf("%lld %d %s\n", time, id, msg);
	}
	pthread_mutex_unlock(&data->state_lock);
	pthread_mutex_unlock(&data->print);
}

void	print_philo_dead(t_data *data, int id)
{
	long long	time;

	pthread_mutex_lock(&data->print);
	time = end_time(data->time_start);
	printf("%lld %d died\n", time, id);
	pthread_mutex_unlock(&data->print);
}
