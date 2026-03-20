#include <pthread.h>
#include <unistd.h>
#include <stdio.h>

int		compteur = 0;
pthread_mutex_t	oui;

void	*incremente(void *args)
{
	int	i;
	int	id;

	id = *(int*)args;
	i = 0;
	while (i < 100)
	{
		pthread_mutex_lock(&oui);
		compteur++;
		pthread_mutex_unlock(&oui);
		printf("id = %d, compteur = %d\n", id, compteur);
		i++;
	}
	return (NULL);
}

int	main(void)
{
	pthread_t t1;
	pthread_t t2;
	int	id1 = 1;
	int id2 = 2;

	pthread_mutex_init(&oui, NULL);

	pthread_create(&t1, NULL, incremente, &id1);
	pthread_create(&t2, NULL, incremente, &id2);

	pthread_join(t1, NULL);
	pthread_join(t2, NULL);

	pthread_mutex_destroy(&oui);

	printf("%d", compteur);
}
