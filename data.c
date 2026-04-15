#include "philo.h"

static void	check_numeric_args(int argc, char **argv);

void	fill_data(t_data *data, int argc, char **argv)
{
	check_numeric_args(argc, argv);
	data->argc = argc;
	data->philo_nb = ft_atol(argv[1]);
	data->time_die = ft_atol(argv[2]);
	data->time_eat = ft_atol(argv[3]);
	data->time_sleep = ft_atol (argv[4]);
	if (argc == 6)
		data->nb_eat_before_stop = ft_atol(argv[5]);
	else
		data->nb_eat_before_stop = -1;
	malloc_philos(data);
	malloc_forks(data);
	link_fork_to_philos(data);
	check_valid_argument(data);
	pthread_mutex_init(&data->print, NULL);
	pthread_mutex_init(&data->state_lock, NULL);
	pthread_mutex_init(&data->start_lock, NULL);
	pthread_cond_init(&data->start_cond, NULL);
	data->start_ready = 0;
	creat_forks(data);
	initate_nb_eat(data);
}

static void	check_numeric_args(int argc, char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (i < argc)
	{
		j = 0;
		if (argv[i][j] == '\0')
			error_exit("invalid numeric argument\n");
		while (argv[i][j])
		{
			if (argv[i][j] < '0' || argv[i][j] > '9')
				error_exit("invalid numeric argument\n");
			j++;
		}
		i++;
	}
}

void	initate_nb_eat(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_nb)
	{
		data->philo[i].nb_eat = 0;
		i++;
	}
}

void	malloc_philos(t_data *data)
{
	data->philo = malloc(sizeof(t_philo) * data->philo_nb);
	if (!data->philo)
		error_exit("malloc problem\n");
	data->monitor = malloc(sizeof(t_monitor));
	if (!data->monitor)
		error_exit("malloc problem\n");
}

void	malloc_forks(t_data *data)
{
	data->forks = malloc(sizeof(pthread_mutex_t) * data->philo_nb);
	if (!data->forks)
		error_exit("malloc problem\n");
}

void	link_fork_to_philos(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_nb)
	{
		data->philo[i].philo_id = i + 1;
		data->philo[i].right_fork = &data->forks[i];
		data->philo[i].left_fork = &data->forks[(i + 1) % data->philo_nb];
		data->philo[i].data = data;
		i++;
	}
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
