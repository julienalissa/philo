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
<<<<<<< HEAD
	pthread_mutex_t	*left_fork; // ok
	pthread_mutex_t *right_fork; // ok
	pthread_t		name; // ok
	long long		last_eat; //ok
	long			nb_eat; //ok
	int				philo_id; // ok
	t_data	*data; // ok
=======
	pthread_t		name;
	int				philo_id;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	long long		last_eat;
	long			nb_eat;
	t_data			*data;
>>>>>>> 505e852 (philo)
}	t_philo;

typedef struct s_monitor
{
	pthread_t		name;
	t_data		*data;
}	t_monitor;

typedef struct s_data
{
<<<<<<< HEAD
	pthread_mutex_t *forks; // ok
	pthread_mutex_t	print; // ok
	pthread_mutex_t	lock_mutex;
	long long	time_start;
	long long		time_die; // ok
	long long		time_eat; // ok
	long long		time_sleep; // ok
	long long		nb_eat_before_stop; // ok
	int			argc;
	int			philo_nb; // ok
	int			stop;
	t_monitor *monitor;
	t_philo *philo;
}	t_data;

// Parcing Data
void		check_valid_argument(t_data *data);
int			not_correct_number_argument(int argc);
void		fill_data(t_data *data, int argc, char **argv);
long		ft_atol(char *str);
void		error_exit(char *error);

// Simulation
void		start_simulation(t_data *data);
void		*philo_routine(void *arg);
=======
	int				stop;
	long long	time_start;
	int				start_ready;
	int				argc;
	int				philo_nb;
	long long		time_die;
	long long		time_eat;
	long long		time_sleep;
	long long		nb_eat_before_stop;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print;
	pthread_mutex_t	state_lock;
	pthread_mutex_t	start_lock;
	pthread_cond_t	start_cond;
	t_monitor		*monitor;
	t_philo			*philo;

}	t_data;

// Parcing Data
void	check_valid_argument(t_data *data);
int		not_correct_number_argument(int argc);
void	fill_data(t_data *data, int argc, char **argv);
long	ft_atol(char *str);
void	error_exit(char *error);
void	creat_forks(t_data *data);
void	malloc_philos(t_data *data);
void	malloc_forks(t_data *data);
void	link_fork_to_philos(t_data *data);
void	initate_nb_eat(t_data *data);

// Simulation
void	start_simulation(t_data *data);
void	*philo_routine(void *arg);
void	go_eat(t_philo *philo);
void	go_sleep(t_philo *philo);
void	go_think(t_philo *philo);
>>>>>>> 505e852 (philo)

// Time
long long	start_time(void);
long long	end_time(long long start);

// print
<<<<<<< HEAD
void		print_it(pthread_mutex_t *lock_it, char  *msg, int id);
=======
void	print_action(t_data *data, int id, const char *msg);
void	print_death(t_data *data, int id);
>>>>>>> 505e852 (philo)

// monitor
void    	*monitor_routine(void *arg);


// routine_utils

int			stop_routine(t_data *data);
void		set_stop(t_data *data);
void		smart_sleep(t_data *data, long long duration_ms);
int			all_full_eat(t_data *data);
int     	check_last_time_eat(t_data *data);

// state
int		get_stop(t_data *data);
void	set_stop(t_data *data);

#endif
