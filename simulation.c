#include "philo.h"

void	creat_philos(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_nb)
	{
		if (pthread_creat(&(data->philo->name), NULL, NULL, NULL) != 0)
			error_exit("probl"); //check leaks
		i++;
	}
}

void	creat_forks(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_nb)
	{
		if (pthread_mutex_init(&(data->forks[i]), NULL) != 0)
			error_exit("probl"); // check leaks
		i++;
	}
}

void	time_to_eat(t_data *data)
{
	int	i;

	i = 0;
	usleep(data->time_eat);

}

void	start_simulation(t_data *data)
{
	(void)data;
	long long begin_time;

	begin_time = start_time();
	creat_philos(data);
	creat_forks(data);
	while (1)
	{
		time_to_eat(data);
		// time_to_sleep(data);
		// time_to_think(data);
	}

}
