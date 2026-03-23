#include "philo.h"



int	main(int argc, char **argv)
{
	t_data	data;

	if (not_correct_number_argument(argc))
		error_exit("need 5 or 6 args check it");
	fill_data(&data, argc, argv);
	check_valid_argument(&data);
	start_simulation(&data);
	// gettimeofday(&(data.end), NULL);
	// printf("%ld", data.end.tv_usec - start.tv_usec);

}
