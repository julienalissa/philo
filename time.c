#include "philo.h"

long long	start_time(void)
{
	struct timeval	start;
	long long		start_sec;

	gettimeofday(&start, NULL);
	start_sec = start.tv_sec * 1000 + start.tv_usec / 1000;
	return (start_sec);
}

long long	end_time(long long start)
{
	struct timeval	end;
	long long		end_sec;
	long long		diff;

	gettimeofday(&end, NULL);
	end_sec = end.tv_sec * 1000 + end.tv_usec / 1000;
	diff = end_sec - start;
	return (diff);
}
