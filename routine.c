#include "philo.h"

<<<<<<< HEAD
void	go_eat(t_philo *philo);
void	go_sleep(t_philo *philo);
void	go_think(t_philo *philo);

void	*monitor_routine(void *arg)
{
    int			i;
    t_data		*data;
    long long	time_since_last_eat;
=======
static void	wait_for_start(t_data *data)
{
    pthread_mutex_lock(&data->start_lock);
    while (!data->start_ready)
        pthread_cond_wait(&data->start_cond, &data->start_lock);
    pthread_mutex_unlock(&data->start_lock);
}

int get_stop(t_data *data)
{
    int stop;

    pthread_mutex_lock(&data->state_lock);
    stop = data->stop;
    pthread_mutex_unlock(&data->state_lock);
    return (stop);
}

void set_stop(t_data *data)
{
    pthread_mutex_lock(&data->state_lock);
    data->stop = 1;
    pthread_mutex_unlock(&data->state_lock);
}

static void smart_sleep_local(t_data *data, long long duration_ms)
{
    long long start;

    start = start_time();
    while (!get_stop(data) && end_time(start) < duration_ms)
        usleep(500);
}

static int everyone_ate_enough(t_data *data)
{
    int i;
    long long target;
>>>>>>> 505e852 (philo)

    data = (t_data *)arg;
    print_it(&data->print, "Monitor created\n", -1);
    while (!stop_routine(data))
    {
        i = 0;
        while (i < data->philo_nb && !stop_routine(data))
        {
            pthread_mutex_lock(&data->lock_mutex);
            time_since_last_eat = end_time(data->philo[i].last_eat);
            pthread_mutex_unlock(&data->lock_mutex);
            if (time_since_last_eat >= data->time_die)
            {
                print_it(&data->print, "The philosopher id dead : ", data->philo[i].philo_id);
                set_stop(data);
                return (NULL);
            }
            i++;
        }
        if (all_full_eat(data))
        {
            set_stop(data);
            return (NULL);
        }
        usleep(1000);
    }
    return (NULL);
}

void	*philo_routine(void *arg)
{
    t_philo	*philo;

    philo = (t_philo *)arg;
    print_it(&philo->data->print, "Philo created : ", philo->philo_id);
    // if (philo->philo_id % 2 == 0)
    //     usleep(1000);
    while (!stop_routine(philo->data))
    {
        go_eat(philo);
        go_sleep(philo);
        go_think(philo);
    }
    return (NULL);
}

void go_eat(t_philo *philo)
{
    pthread_mutex_t *first_fork;
    pthread_mutex_t *second_fork;

    if (philo->data->philo_nb == 1)
    {
        pthread_mutex_lock(philo->right_fork);
        print_action(philo->data, philo->philo_id, "has taken a fork");
        smart_sleep_local(philo->data, philo->data->time_die + 1);
        pthread_mutex_unlock(philo->right_fork);
        return;
    }
    if (philo->philo_id % 2 == 0)
    {
        first_fork = philo->right_fork;
        second_fork = philo->left_fork;
    }
    else
    {
        first_fork = philo->left_fork;
        second_fork = philo->right_fork;
    }
    pthread_mutex_lock(first_fork);
<<<<<<< HEAD
    print_it(&philo->data->print, "Take fork\n", -1);
    if (stop_routine(philo->data))
=======
    print_action(philo->data, philo->philo_id, "has taken a fork");
    if (get_stop(philo->data))
>>>>>>> 505e852 (philo)
    {
        pthread_mutex_unlock(first_fork);
        return;
    }
    pthread_mutex_lock(second_fork);
<<<<<<< HEAD
    print_it(&philo->data->print, "Take fork\n", -1);
    pthread_mutex_lock(&philo->data->lock_mutex);
    philo->last_eat = start_time();
    philo->nb_eat++;
    pthread_mutex_unlock(&philo->data->lock_mutex);
    print_it(&philo->data->print, "I am eating\n", philo->philo_id);
    smart_sleep(philo->data, philo->data->time_eat);
=======
    print_action(philo->data, philo->philo_id, "has taken a fork");
    pthread_mutex_lock(&philo->data->state_lock);
    philo->last_eat = start_time();
    philo->nb_eat++;
    pthread_mutex_unlock(&philo->data->state_lock);
    print_action(philo->data, philo->philo_id, "is eating");
    smart_sleep_local(philo->data, philo->data->time_eat);
>>>>>>> 505e852 (philo)
    pthread_mutex_unlock(second_fork);
    pthread_mutex_unlock(first_fork);
}

void go_sleep(t_philo *philo)
{
<<<<<<< HEAD
    if (stop_routine(philo->data))
        return ;
    print_it(&philo->data->print, "I go sleep\n", philo->philo_id);
    smart_sleep(philo->data, philo->data->time_sleep);
=======
    if (get_stop(philo->data))
        return;
    print_action(philo->data, philo->philo_id, "is sleeping");
    smart_sleep_local(philo->data, philo->data->time_sleep);
>>>>>>> 505e852 (philo)
}

void go_think(t_philo *philo)
{
<<<<<<< HEAD
    if (stop_routine(philo->data))
        return ;
    print_it(&philo->data->print, "Let me think\n", philo->philo_id);
    usleep(1000);
}

=======
    if (get_stop(philo->data))
        return;
    print_action(philo->data, philo->philo_id, "is thinking");
    usleep(1000);
}

void *philo_routine(void *arg)
{
    t_philo *philo;

    philo = (t_philo *)arg;
	wait_for_start(philo->data);
    if (philo->philo_id % 2 == 0)
        usleep(1000);
    while (!get_stop(philo->data))
    {
        go_eat(philo);
        go_sleep(philo);
        go_think(philo);
    }
    return (NULL);
}

void *monitor_routine(void *arg)
{
    int i;
    int dead_id;
    t_data *data;
    long long time_since_last_eat;

    data = (t_data *)arg;
	wait_for_start(data);
    while (!get_stop(data))
    {
        i = 0;
        dead_id = 0;
        while (i < data->philo_nb && !dead_id)
        {
            pthread_mutex_lock(&data->state_lock);
            time_since_last_eat = end_time(data->philo[i].last_eat);
            if (!data->stop && time_since_last_eat >= data->time_die)
            {
                data->stop = 1;
                dead_id = data->philo[i].philo_id;
            }
            pthread_mutex_unlock(&data->state_lock);
            i++;
        }
        if (dead_id)
        {
            print_death(data, dead_id);
            return (NULL);
        }
        if (everyone_ate_enough(data))
        {
            set_stop(data);
            return (NULL);
        }
        usleep(1000);
    }
    return (NULL);
}
>>>>>>> 505e852 (philo)
