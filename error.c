#include "philo.h"

int	not_correct_number_argument(int argc)
{
	if (argc != 5 && argc != 6)
		return (1);
	else
		return (0);
}

void	error_exit(char *error)
{
	printf("%s", error);
	// free si besoin
	exit(1);
}

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

