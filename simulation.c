#include "philo.h"

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	(void)philo;
	//manger
	// dormir
	// pnser
	return (NULL);
}

void	creat_philos(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_nb)
	{
		if (pthread_mutex_init(&(data->forks[i]), NULL) != 0)
			error_exit("prob");
		i++;
	}
}

void	creat_forks(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_nb)
	{
		if (pthread_create(&(data->philo[i].name), NULL,
				philo_routine, &data->philo[i]) != 0)
			error_exit("prob");
		i++;
	}
}

void	start_simulation(t_data *data)
{
	data->time_start = start_time();
	creat_forks(data);
	creat_philos(data);
	while (1)
	{
		time_to_eat(data);
		// time_to_sleep(data);
		// time_to_think(data);
	}
}
