/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   utils.c                                             :+:    :+:           */
/*                                                      +:+                   */
/*   By: jualissa <marvin@42.fr>                       +#+                    */
/*                                                    +#+                     */
/*   Created: 2026/06/22 18:54:37 by jualissa       #+#    #+#                */
/*   Updated: 2026/06/22 18:54:39 by jualissa       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	smart_sleep_local(t_data *data, long long duration_ms)
{
	long long	start;

	start = start_time();
	while (!stop_simu(data) && end_time(start) < duration_ms)
		usleep(500);
}

void	set_stop(t_data *data)
{
	pthread_mutex_lock(&data->state_lock);
	data->stop = 1;
	pthread_mutex_unlock(&data->state_lock);
}
