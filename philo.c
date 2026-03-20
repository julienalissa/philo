#include "philo.h"

int	main(int argc, char **argv)
{
	t_data	data;

	struct timeval start;
	struct timeval end;
	gettimeofday(&start, NULL);
	if (not_correct_number_argument(argc))
		error_exit("need 5 or 6 args check it");
	fill_data(&data, argc, argv);
	check_valid_argument(&data);
	gettimeofday(&end, NULL);
	printf("%ld", end.tv_sec - start.tv_sec);
}
