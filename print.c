#include "philo.h"

void    print_it(pthread_mutex_t *lock_it, char  *msg, int id)
{
    pthread_mutex_lock(lock_it);
    printf("%s", msg);
    if (id != -1)
        printf("%d\n", id);
    pthread_mutex_unlock(lock_it);
}