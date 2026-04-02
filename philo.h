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
	pthread_t		name; // ok
	int				philo_id; // ok
	pthread_mutex_t	*left_fork; // ok
	pthread_mutex_t *right_fork; // ok
	long long		last_eat; //ok
	long			nb_eat; //ok
	t_data	*data; // ok
}	t_philo;

typedef struct s_monitor
{
	pthread_t		name;
	t_data		*data;
}	t_monitor;

typedef struct s_data
{
	int			stop;
	long long	time_start;
	int			argc;
	int			philo_nb; // ok
	long long		time_die; // ok
	long long		time_eat; // ok
	long long		time_sleep; // ok
	long long		nb_eat_before_stop; // ok
	pthread_mutex_t *forks; // ok
	pthread_mutex_t	print; // ok
	pthread_mutex_t	state_lock;
	t_monitor *monitor;
	t_philo *philo;

}	t_data;

// Parcing Data
void	check_valid_argument(t_data *data);
int		not_correct_number_argument(int argc);
void	fill_data(t_data *data, int argc, char **argv);
long	ft_atol(char *str);
void	error_exit(char *error);
void	creat_forks(t_data *data);

// Simulation
void	start_simulation(t_data *data);
void	*philo_routine(void *arg);

// Time
long long	start_time(void);
long long	end_time(long long start);

// print
void    print_it(pthread_mutex_t *lock_it, char  *msg, int id);

// monitor
void    *monitor_routine(void *arg);

#endif
