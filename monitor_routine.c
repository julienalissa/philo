#include "philo.h"

static int	everyone_ate_enough(t_data *data);
static void	set_stop(t_data *data);

void	*monitor_routine(void *arg)
{
    t_data		*data;
	int			i;

	data = (t_data *)arg;
	wait_for_start(data);
	while (!stop_simu(data))
	{
		i = 0;
		data->monitor->philo_dead_id = 0;
		while (i < data->philo_nb && !data->monitor->philo_dead_id)
		{
			pthread_mutex_lock(&data->state_lock);
			data->monitor->time_last_eat = end_time(data->philo[i].last_eat);
			if (!data->stop && data->monitor->time_last_eat >= data->time_die)
			{
				data->stop = 1;
				data->monitor->philo_dead_id = data->philo[i].philo_id;
			}
			pthread_mutex_unlock(&data->state_lock);
			i++;
		}
		if (data->monitor->philo_dead_id)
		{
			print_philo_dead(data, data->monitor->philo_dead_id);
			return (NULL);
		}
		if (everyone_ate_enough(data))
		{
			set_stop(data);
			return (NULL);
		}
		usleep(1000);
	}
	return (NULL);
}

void	wait_for_start(t_data *data)
{
	pthread_mutex_lock(&data->start_lock);
	while (!data->start_simulation)
		pthread_cond_wait(&data->start_cond, &data->start_lock);
	pthread_mutex_unlock(&data->start_lock);
}

int	stop_simu(t_data *data)
{
	int	stop;

	pthread_mutex_lock(&data->state_lock);
	stop = data->stop;
	pthread_mutex_unlock(&data->state_lock);
	return (stop);
}

static int	everyone_ate_enough(t_data *data)
{
	int			i;

	if (data->nb_eat_before_stop == -1)
		return (0);
	pthread_mutex_lock(&data->state_lock);
	i = 0;
	while (i < data->philo_nb)
	{
		if (data->philo[i].nb_eat < data->nb_eat_before_stop)
		{
			pthread_mutex_unlock(&data->state_lock);
			return (0);
		}
		i++;
	}
	pthread_mutex_unlock(&data->state_lock);
	return (1);
}

static void	set_stop(t_data *data)
{
	pthread_mutex_lock(&data->state_lock);
	data->stop = 1;
	pthread_mutex_unlock(&data->state_lock);
}
