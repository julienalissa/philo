#include "philo.h"

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
