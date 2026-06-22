/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   monitor_routine.c                                   :+:    :+:           */
/*                                                      +:+                   */
/*   By: jualissa <marvin@42.fr>                       +#+                    */
/*                                                    +#+                     */
/*   Created: 2026/06/20 19:44:44 by jualissa       #+#    #+#                */
/*   Updated: 2026/06/20 19:44:45 by jualissa       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	everyone_ate_enough(t_data *data);
static int	check_philosophers(t_data *data);

void	*monitor_routine(void *arg)
{
	t_data		*data;

	data = (t_data *)arg;
	wait_for_start(data);
	while (!stop_simu(data))
	{
		if (check_philosophers(data))
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

static int	check_philosophers(t_data *data)
{
	int	i;

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
	return (data->monitor->philo_dead_id);
}

void	wait_for_start(t_data *data)
{
	int	started;

	started = 0;
	while (!started)
	{
		pthread_mutex_lock(&data->start_lock);
		started = data->start_simulation;
		pthread_mutex_unlock(&data->start_lock);
		if (!started)
			usleep(100);
	}
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
