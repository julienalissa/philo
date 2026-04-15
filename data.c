#include "philo.h"

static void	check_numeric_args(int argc, char **argv);
static void	malloc_philos(t_data *data);
static void	malloc_forks(t_data *data);
static void	link_fork_to_philos(t_data *data);

void	fill_data(t_data *data, int argc, char **argv)
{
	check_numeric_args(argc, argv); // check if it's only nb
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
	data->start_simulation = 0;
	creat_forks(data);
	initate_nb_eat(data);
	data->stop = 0;
	data->start_simulation = 0;
	data->monitor->time_last_eat = -1;
	data->monitor->philo_dead_id = -1;
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

static void	malloc_philos(t_data *data)
{
	data->philo = malloc(sizeof(t_philo) * data->philo_nb);
	if (!data->philo)
		error_exit("malloc problem\n");
	data->monitor = malloc(sizeof(t_monitor));
	if (!data->monitor)
		error_exit("malloc problem\n");
}

static void	malloc_forks(t_data *data)
{
	data->forks = malloc(sizeof(pthread_mutex_t) * data->philo_nb);
	if (!data->forks)
		error_exit("malloc problem\n");
}

static void	link_fork_to_philos(t_data *data)
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
