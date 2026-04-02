#include "philo.h"

static int	get_stop(t_data *data)
{
    int	stop;

    pthread_mutex_lock(&data->state_lock);
    stop = data->stop;
    pthread_mutex_unlock(&data->state_lock);
    return (stop);
}

static void	set_stop(t_data *data)
{
    pthread_mutex_lock(&data->state_lock);
    data->stop = 1;
    pthread_mutex_unlock(&data->state_lock);
}

static void	smart_sleep(t_data *data, long long duration_ms)
{
    long long	start;

    start = start_time();
    while (!get_stop(data) && end_time(start) < duration_ms)
        usleep(500);
}

static int	everyone_ate_enough(t_data *data)
{
    int			i;
    long long	target;

    if (data->nb_eat_before_stop == -1)
        return (0);
    target = data->nb_eat_before_stop;
    pthread_mutex_lock(&data->state_lock);
    i = 0;
    while (i < data->philo_nb)
    {
        if (data->philo[i].nb_eat < target)
        {
            pthread_mutex_unlock(&data->state_lock);
            return (0);
        }
        i++;
    }
    pthread_mutex_unlock(&data->state_lock);
    return (1);
}

void	go_eat(t_philo *philo)
{
    pthread_mutex_t	*first_fork;
    pthread_mutex_t	*second_fork;

    if (philo->data->philo_nb == 1)
    {
        pthread_mutex_lock(philo->right_fork);
        print_it(&philo->data->print, "Take right fork\n", -1);
        smart_sleep(philo->data, philo->data->time_die);
        pthread_mutex_unlock(philo->right_fork);
        return ;
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
    print_it(&philo->data->print, "Take fork\n", -1);
    if (get_stop(philo->data))
    {
        pthread_mutex_unlock(first_fork);
        return ;
    }
    pthread_mutex_lock(second_fork);
    print_it(&philo->data->print, "Take fork\n", -1);
    pthread_mutex_lock(&philo->data->state_lock);
    philo->last_eat = start_time();
    philo->nb_eat++;
    pthread_mutex_unlock(&philo->data->state_lock);
    print_it(&philo->data->print, "I am eating\n", philo->philo_id);
    smart_sleep(philo->data, philo->data->time_eat);
    pthread_mutex_unlock(second_fork);
    pthread_mutex_unlock(first_fork);
}

void	go_sleep(t_philo *philo)
{
    if (get_stop(philo->data))
        return ;
    print_it(&philo->data->print, "I go sleep\n", philo->philo_id);
    smart_sleep(philo->data, philo->data->time_sleep);
}

void	go_think(t_philo *philo)
{
    if (get_stop(philo->data))
        return ;
    print_it(&philo->data->print, "Let me think\n", philo->philo_id);
    usleep(1000);
}

void	*philo_routine(void *arg)
{
    t_philo	*philo;

    philo = (t_philo *)arg;
    print_it(&philo->data->print, "Philo created : ", philo->philo_id);
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

void	*monitor_routine(void *arg)
{
    int			i;
    t_data		*data;
    long long	time_since_last_eat;

    data = (t_data *)arg;
    print_it(&data->print, "Monitor created\n", -1);
    while (!get_stop(data))
    {
        i = 0;
        while (i < data->philo_nb && !get_stop(data))
        {
            pthread_mutex_lock(&data->state_lock);
            time_since_last_eat = end_time(data->philo[i].last_eat);
            pthread_mutex_unlock(&data->state_lock);
            if (time_since_last_eat >= data->time_die)
            {
                print_it(&data->print, "A philosopher died : ", data->philo[i].philo_id);
                set_stop(data);
                return (NULL);
            }
            i++;
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