#ifndef PHILO_H
#define PHILO_H

#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/time.h>
#include <limits.h>

typedef struct s_data t_data;
typedef struct s_philo t_philo;



typedef struct s_philo
{
	pthread_t		name;
	int				philo_id;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t *right_fork;
	t_data	*data;
	long			last_eat;
	long			nb_eat;
}	t_philo;

typedef struct s_data
{
	long long	time_start;
	int			argc;
	int			philo_nb;
	long		time_die;
	long		time_eat;
	long		time_sleep;
	long		time_philo_nb;
	pthread_mutex_t *forks;
	t_philo *philo;
}	t_data;

// Parcing Data
void	check_valid_argument(t_data *data);
int		not_correct_number_argument(int argc);
void	fill_data(t_data *data, int argc, char **argv);
long	ft_atol(char *str);
void	error_exit(char *error);

// Simulation
void	start_simulation(t_data *data);
void	*philo_routine(void *arg);

// Time
long long	start_time(void);
long long	end_time(long long start);

#endif
