#include "philo.h"

void	*philo_routine(void *arg);
void	creat_and_start_routine(t_data *data);

void	start_simulation(t_data *data)
{
	data->time_start = start_time();
	creat_and_start_routine(data);
}

void	creat_and_start_routine(t_data *data)
{
	int	i;

	i = 0;
	if (pthread_create(&(data->monitor->name), NULL,
				monitor_routine, data) != 0)
			printf("monitor marche pas"); //error_exit("prob");
	while (i < data->philo_nb)
	{
		if (pthread_create(&(data->philo[i].name), NULL,
				philo_routine, &data->philo[i]) != 0)
			printf("marche pas"); //error_exit("prob");
		i++;
	}
	i = 0;
	while (i < data->philo_nb)
	{
		pthread_join(data->philo[i].name, NULL);
		i++;
	}
	pthread_join(data->monitor->name, NULL);
}

void	creat_forks(t_data *data)
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






