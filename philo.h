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
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	t_data			*data;
	long long		last_eat;
	long			nb_eat;
	int				philo_id;
}	t_philo;

typedef struct s_monitor
{
	pthread_t		name;
	t_data			*data;
	long long		time_last_eat;
	int				philo_dead_id;
}	t_monitor;

typedef struct s_data
{
	pthread_cond_t	start_cond;
	pthread_mutex_t	print;
	pthread_mutex_t	state_lock;
	pthread_mutex_t	start_lock;
	pthread_mutex_t	*forks;
	t_monitor		*monitor;
	t_philo			*philo;
	long long		time_die;
	long long		time_eat;
	long long		time_sleep;
	long long		nb_eat_before_stop;
	long long		time_start;
	int				stop;
	int				start_simulation;
	int				argc;
	int				philo_nb;
}	t_data;

// main
int		not_correct_number_argument(int argc);
void	fill_data(t_data *data, int argc, char **argv);
void	error_exit(char *error);

// fill_data
long	ft_atol(char *str);
void	check_valid_argument(t_data *data);
void	creat_forks(t_data *data);
void	initate_nb_eat(t_data *data);

// monitor_routine
int		stop_simu(t_data *data);
void	start_simulation(t_data *data);
void    *monitor_routine(void *arg);
void	wait_for_start(t_data *data);

// philo_routine
void	*philo_routine(void *arg);

// Time
long long	start_time(void);
long long	end_time(long long start);

// print
void	print_action(t_data *data, int id, const char *msg);
void	print_philo_dead(t_data *data, int id);

#endif
