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
    print_it(&philo->data->print, "philo created : ", philo->philo_id);
    while (1)
    {
        // check_all(philo);
        go_eat(philo);
        // check_all(philo);
        go_sleep(philo);
        // check_all(philo);
        go_think(philo);
        i++;
    }

    return (NULL);
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
        print_it(&philo->data->print, "Take left fork\n", -1);
        pthread_mutex_lock(philo->left_fork);
        print_it(&philo->data->print, "Take right fork\n", -1);
    }
    else
    {
        pthread_mutex_lock(philo->left_fork);
        print_it(&philo->data->print, "Take right fork\n", -1);
        pthread_mutex_lock(philo->right_fork);
        print_it(&philo->data->print, "Take left fork\n", -1);
    }
    incremente_eat_nb(philo);
    print_it(&philo->data->print, "I am eating\n", -1);
    usleep(philo->data->time_eat * 1000);
    pthread_mutex_unlock(philo->right_fork);
    pthread_mutex_unlock(philo->left_fork);

}

void    incremente_eat_nb(t_philo   *philo)
{
    pthread_mutex_t lock;

    pthread_mutex_init(&lock, NULL);
    pthread_mutex_lock(&lock);
    philo->nb_eat++;
    pthread_mutex_unlock(&lock);
    pthread_mutex_destroy(&lock);
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