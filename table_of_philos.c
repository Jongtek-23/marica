#include "philo.h"

int	table_of_philos(t_all *all)
{
	int		i;

	all->forks = malloc(sizeof(pthread_mutex_t) * all->nb_of_philos);
	if (!all->forks)
		return (1);
	i = 0;
	while (i < all->nb_of_philos)
	{
		pthread_mutex_init(&all->forks[i], NULL);
		i++;
	}
	pthread_mutex_init(&all->phrase, NULL);
	pthread_mutex_init(&all->manger, NULL);
	pthread_mutex_init(&all->mourir, NULL);
	all->debut_dinner = calc_time();
	all->est_mort = 0;
	return (0);
}