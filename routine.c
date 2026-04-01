#include "philo.h"

void    go_eat(t_philo *philo);
void    go_sleep(t_philo *philo);
void    go_think(t_philo *philo);
int     not_finish_total_eating(t_philo *philo);
void    incremente_eat_nb(t_philo   *philo);

void	*philo_routine(void *arg)
{
    t_philo *philo;
    philo = (t_philo *)arg;
    print_it(&philo->data->print, "Philo created : ", philo->philo_id);
    while (1)
    {
        // check_all(philo);
        go_eat(philo);
        // check_all(philo);
        go_sleep(philo);
        // check_all(philo);
        go_think(philo);
    }

    return (NULL);
}

void    *monitor_routine(void *arg)
{
    int i;
    t_data *data;
    long long end;

    i = 0;
    data = (t_data *)arg;
    print_it(&data->print, "Monitor created", -1);
    while (1)
    {
        i = 0;
        while (i < data->philo_nb)
        {
            end = end_time(data->philo[i].last_eat);
            // printf("%lld", end);
            printf("\nend = %lld, time die = %lld\n", end, data->time_die);
            if (end >= data->time_die)
                exit(1);
            // exit(1);
    //       if (monitor->data->nb_eat_before_stop != -1 && monitor->data->nb_eat_before_stop <= monitor->data->nb_eat)
    //            error_exit("Ils ont tous monger");////////////////attention
            i++;
        }
    }

}

// void check_all(t_philo *philo)
// {
    // if (philo->data->nb_eat_before_stop != -1 && philo->data->nb_eat_before_stop <= philo->nb_eat)
        // free le tout et exit;
    // if ()
// }

void    go_eat(t_philo *philo)
{
    if (philo->philo_id % 2 == 0)
    {
        pthread_mutex_lock(philo->right_fork);
        print_it(&philo->data->print, "Take right fork\n", -1);
        pthread_mutex_lock(philo->left_fork);
        print_it(&philo->data->print, "Take left fork\n", -1);
    }
    else
    {
        pthread_mutex_lock(philo->left_fork);
        print_it(&philo->data->print, "Take left fork\n", -1);
        pthread_mutex_lock(philo->right_fork);
        print_it(&philo->data->print, "Take right fork\n", -1);
    }
    philo->nb_eat++;
    print_it(&philo->data->print, "I am eating\n", -1);
    philo->last_eat = start_time();
    usleep(philo->data->time_eat * 1000);
    philo->last_eat = start_time();
    pthread_mutex_unlock(philo->right_fork);
    pthread_mutex_unlock(philo->left_fork);

}

void    go_sleep(t_philo *philo)
{
    print_it(&philo->data->print, "I go sleep\n", -1);
    usleep(philo->data->time_sleep * 1000);
}

void    go_think(t_philo *philo)
{
    print_it(&philo->data->print, "Let me think \n", -1);
    usleep(1000);
}