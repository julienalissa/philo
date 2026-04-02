#include "philo.h"

void	go_eat(t_philo *philo);
void	go_sleep(t_philo *philo);
void	go_think(t_philo *philo);

void	*monitor_routine(void *arg)
{
    int			i;
    t_data		*data;
    long long	time_since_last_eat;

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
    if (stop_routine(philo->data))
    {
        pthread_mutex_unlock(first_fork);
        return ;
    }
    pthread_mutex_lock(second_fork);
    print_it(&philo->data->print, "Take fork\n", -1);
    pthread_mutex_lock(&philo->data->lock_mutex);
    philo->last_eat = start_time();
    philo->nb_eat++;
    pthread_mutex_unlock(&philo->data->lock_mutex);
    print_it(&philo->data->print, "I am eating\n", philo->philo_id);
    smart_sleep(philo->data, philo->data->time_eat);
    pthread_mutex_unlock(second_fork);
    pthread_mutex_unlock(first_fork);
}

void	go_sleep(t_philo *philo)
{
    if (stop_routine(philo->data))
        return ;
    print_it(&philo->data->print, "I go sleep\n", philo->philo_id);
    smart_sleep(philo->data, philo->data->time_sleep);
}

void	go_think(t_philo *philo)
{
    if (stop_routine(philo->data))
        return ;
    print_it(&philo->data->print, "Let me think\n", philo->philo_id);
    usleep(1000);
}

