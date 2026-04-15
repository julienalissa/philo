#include "philo.h"

int	not_correct_number_argument(int argc)
{
	if (argc != 5 && argc != 6)
		return (1);
	return (0);
}

void	error_exit(char *error)
{
	printf("%s", error);
	exit(1);
}

