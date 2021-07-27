#include "philo.h"

void		clean_table(t_all *all, t_philo *philos)
{
	int		i;

	i = 0;
	while (i < all->nb_of_philos)
	{
		pthread_join(philos[i].philo_thread, NULL);
		i++;
	}
	i = 0;
	while (i < all->nb_of_philos)
	{
		pthread_mutex_destroy(&all->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&all->phrase);
	pthread_mutex_destroy(&all->manger);
	pthread_mutex_destroy(&all->mourir);
	free(all->forks);
	free(philos);
}

int	values_of_args(t_all *all, int argc, char *argv[])
{
    int i;

    i = 1;
    all->each_must_eat = -1;
    while (argv[i])
    {
        if (ft_is_str_number(argv[i]))
            return (ft_error("Error: Put numbers please!\n"));
        i++;
    }
	all->nb_of_philos = ft_atoi(argv[1]);
	all->time_to_die = ft_atoi(argv[2]);
	all->time_to_eat = ft_atoi(argv[3]);
	all->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		all->each_must_eat = ft_atoi(argv[5]);
    return (0);
}

int	verif_values_of_args(t_all *all, int argc)
{
	if (all->nb_of_philos <= 0)
		return (ft_error("Error: number of philos\n"));
	if (all->time_to_die < 0)
		return (ft_error("Error: time to die\n"));
	if (all->time_to_eat < 0)
		return (ft_error("Error: time to eat\n"));
	if (all->time_to_sleep < 0)
		return (ft_error("Error: time to sleep\n"));
	if (argc == 6 && all->each_must_eat <= 0)
		return (ft_error("Error: num of each must eat\n"));
	return (0);
}

int			main(int argc, char **argv)
{
	t_all	all;
	t_philo	*philos;

	if (5 != argc && argc != 6)
		return (ft_error("Error: put right number of arguments\n"));
	if (values_of_args(&all, argc, argv))
        return (1);
	if (verif_values_of_args(&all, argc))
		return (1);
	if (table_of_philos(&all))
		return (ft_error("Error: malloc failed\n"));
	philos = malloc((sizeof(t_philo) * all.nb_of_philos));
	if (!philos)
		return (1);
	init_philos(&all, philos);
	clean_table(&all, philos);
	return (0);
}
