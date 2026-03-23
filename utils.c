#include "philo.h"

void	check_valid_argument(t_data *data)
{
	if (data->philo_nb < 1 || data->philo_nb > 200)
		error_exit("number of philo cant be negatif or > 200\n");
	if (data->time_die < 1)
		error_exit("time to die cant be negatif or > LONG MAX\n");
	if (data->time_eat < 1)
		error_exit("time to eat cant be negatif or > LONG MAX\n");
	if (data->time_eat < 1)
		error_exit("time to sleep cant be negatif or > LONG MAX\n");
	if (data->argc == 6 && data->time_philo_nb < 1)
		error_exit("nb time philo must eat cant be negatif or > LONG MAX\n");
}

int	not_correct_number_argument(int argc)
{
	if (argc != 5 && argc != 6)
		return (1);
	else
		return (0);
}

void	malloc_philos(t_data *data)
{
	int	i;

	i = 0;
	data->philo = malloc(sizeof(t_philo) * data->philo_nb);
	if (!data->philo)
		return;
}

void	malloc_forks(t_data *data)
{
	int	i;

	i = 0;
	data->forks = malloc(sizeof(pthread_mutex_t) * data->philo_nb);
	if (!data->forks)
		return ;
}

void	link_fork_to_philos(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_nb)
	{
		data->philo[i].left_fork = &data->forks[i + 1];
		data->philo[i].right_fork = &data->forks[i];
		i++;
	}
	data->philo[i].left_fork = &data->forks[0];
}

void	fill_data(t_data *data, int argc, char **argv)
{
	data->argc = argc;
	data->philo_nb = ft_atol(argv[1]);
	data->time_die = ft_atol(argv[2]);
	data->time_eat = ft_atol(argv[3]);
	data->time_sleep = ft_atol (argv[4]);
	if (argc == 6)
		data->time_philo_nb = ft_atol(argv[5]);
	else
		data->time_philo_nb = -1;
	malloc_philos(data);
	malloc_forks(data);
	link_fork_to_philos(data);
}

long	ft_atol(char *str)
{
	long	nb;
	int		i;

	nb = 0;
	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '+' || str[i] == '-')
		if (str[i++] == '-')
			return (-1);
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (nb > (LONG_MAX - (str[i] - '0')) / 10)
			return (-1);
		nb = nb * 10 + (str[i++] - '0');
	}
	return (nb);
}

void	error_exit(char *error)
{
	printf("%s", error);
	//free_if need
	exit(1);
}

