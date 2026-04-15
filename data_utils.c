#include "philo.h"

void	check_valid_argument(t_data *data)
{
	if (data->philo_nb < 1 || data->philo_nb > 200)
		error_exit("number of philo cant be negatif or > 200\n");
	if (data->time_die < 1)
		error_exit("time to die cant be negatif or > LONG MAX\n");
	if (data->time_eat < 1)
		error_exit("time to eat cant be negatif or > LONG MAX\n");
	if (data->time_sleep < 1)
		error_exit("time to sleep cant be negatif or > LONG MAX\n");
	if (data->argc == 6 && data->nb_eat_before_stop < 1)
		error_exit("nb time philo must eat cant be negatif or > LONG MAX\n");
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

