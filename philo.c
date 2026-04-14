/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motde <motde@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/11 18:00:00 by motde             #+#    #+#             */
/*   Updated: 2026/04/11 18:00:00 by motde            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	destroy_and_free(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_nb)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&data->print);
	pthread_mutex_destroy(&data->state_lock);
	pthread_mutex_destroy(&data->start_lock);
	pthread_cond_destroy(&data->start_cond);
	free(data->forks);
	free(data->monitor);
	free(data->philo);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (not_correct_number_argument(argc))
		error_exit("need 5 or 6 args check it");
	fill_data(&data, argc, argv);
	start_simulation(&data);
	destroy_and_free(&data);
	return (0);
}
