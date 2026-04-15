#include "philo.h"

void	start_simulation(t_data *data)
{
	int	i;

	i = 0;
	if (pthread_create(&(data->monitor->name), NULL,
				monitor_routine, data) != 0)
			error_exit("thread creation failed"); // il faut pas oublier de bien exit stp
	while (i < data->philo_nb)
	{
		if (pthread_create(&(data->philo[i].name), NULL,
				philo_routine, &data->philo[i]) != 0)
			error_exit("thread creation failed");
		i++;
	}
	pthread_mutex_lock(&data->start_lock);
	data->time_start = start_time();
	i = 0;
	while (i < data->philo_nb)
	{
		data->philo[i].last_eat = data->time_start;
		i++;
	}
	data->start_simulation = 1;
	pthread_cond_broadcast(&data->start_cond);
	pthread_mutex_unlock(&data->start_lock);
	i = 0;
	while (i < data->philo_nb)
	{
		pthread_join(data->philo[i].name, NULL);
		i++;
	}
	pthread_join(data->monitor->name, NULL);
}
