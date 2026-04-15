#include "philo.h"

static void	go_eat(t_philo *philo);
static void	go_sleep(t_philo *philo);
static void	go_think(t_philo *philo);
static void	smart_sleep_local(t_data *data, long long duration_ms);

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

	if (philo->data->philo_nb == 1)
	{
		pthread_mutex_lock(philo->right_fork);
		print_action(philo->data, philo->philo_id, "has taken a fork");
		smart_sleep_local(philo->data, philo->data->time_die + 1);
		pthread_mutex_unlock(philo->right_fork);
		return ;
	}
	if (philo->philo_id % 2 == 0)
	{
		first_fork = philo->right_fork;
		second_fork = philo->left_fork;
	}
	else
	{
		first_fork = philo->left_fork;
		second_fork = philo->right_fork;
	}
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
	print_action(philo->data, philo->philo_id, "eating");
	smart_sleep_local(philo->data, philo->data->time_eat);
	pthread_mutex_unlock(second_fork);
	pthread_mutex_unlock(first_fork);
}

static void	go_sleep(t_philo *philo)
{
	if (stop_simu(philo->data))
		return ;
	print_action(philo->data, philo->philo_id, "sleeping");
	smart_sleep_local(philo->data, philo->data->time_sleep);
}

static void	go_think(t_philo *philo)
{
	if (stop_simu(philo->data))
		return ;
	print_action(philo->data, philo->philo_id, "thinking");
	usleep(1000);
}

static void	smart_sleep_local(t_data *data, long long duration_ms)
{
	long long	start;

	start = start_time();
	while (!stop_simu(data) && end_time(start) < duration_ms)
		usleep(500);
}
