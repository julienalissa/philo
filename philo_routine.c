/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   philo_routine.c                                     :+:    :+:           */
/*                                                      +:+                   */
/*   By: jualissa <marvin@42.fr>                       +#+                    */
/*                                                    +#+                     */
/*   Created: 2026/06/20 19:44:51 by jualissa       #+#    #+#                */
/*   Updated: 2026/06/20 19:44:52 by jualissa       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	go_eat(t_philo *philo);
static void	go_sleep(t_philo *philo);
static void	go_think(t_philo *philo);
void		smart_sleep_local(t_data *data, long long duration_ms);
static int	take_forks(t_philo *philo, pthread_mutex_t **f1,
				pthread_mutex_t **f2);

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	wait_for_start(philo->data);
	if (philo->philo_id % 2 == 0)
		usleep(1000);
	while (!stop_simu(philo->data))
	{
		go_eat(philo);
		go_sleep(philo);
		go_think(philo);
	}
	return (NULL);
}

static void	go_eat(t_philo *philo)
{
	pthread_mutex_t	*first_fork;
	pthread_mutex_t	*second_fork;

	if (take_forks(philo, &first_fork, &second_fork))
		return ;
	pthread_mutex_lock(first_fork);
	print_action(philo->data, philo->philo_id, "has taken a fork");
	if (stop_simu(philo->data))
	{
		pthread_mutex_unlock(first_fork);
		return ;
	}
	pthread_mutex_lock(second_fork);
	print_action(philo->data, philo->philo_id, "has taken a fork");
	pthread_mutex_lock(&philo->data->state_lock);
	philo->last_eat = start_time();
	philo->nb_eat++;
	pthread_mutex_unlock(&philo->data->state_lock);
	print_action(philo->data, philo->philo_id, "is eating");
	smart_sleep_local(philo->data, philo->data->time_eat);
	pthread_mutex_unlock(second_fork);
	pthread_mutex_unlock(first_fork);
}

static int	take_forks(t_philo *philo,
			pthread_mutex_t **f1, pthread_mutex_t **f2)
{
	if (philo->data->philo_nb == 1)
	{
		pthread_mutex_lock(philo->right_fork);
		print_action(philo->data, philo->philo_id, "has taken a fork");
		smart_sleep_local(philo->data, philo->data->time_die + 1);
		pthread_mutex_unlock(philo->right_fork);
		return (1);
	}
	if (philo->philo_id % 2 == 0)
	{
		*f1 = philo->right_fork;
		*f2 = philo->left_fork;
	}
	else
	{
		*f1 = philo->left_fork;
		*f2 = philo->right_fork;
	}
	return (0);
}

static void	go_sleep(t_philo *philo)
{
	if (stop_simu(philo->data))
		return ;
	print_action(philo->data, philo->philo_id, "is sleeping");
	smart_sleep_local(philo->data, philo->data->time_sleep);
}

static void	go_think(t_philo *philo)
{
	if (stop_simu(philo->data))
		return ;
	print_action(philo->data, philo->philo_id, "is thinking");
	usleep(1000);
}
