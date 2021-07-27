#include "philo.h"

int  a_manger(t_philo *philo)
{
	t_all			*all;

	all = philo->all;
	pthread_mutex_lock(&all->forks[philo->left]);
	print_phrase(philo, TAKE_FORK, get_time());
	pthread_mutex_lock(&all->forks[philo->right]);
	print_phrase(philo, TAKE_FORK, get_time());
	print_phrase(philo, EATING, get_time());
	my_sleep(philo->all->time_to_eat);
	pthread_mutex_unlock(&all->forks[philo->left]);
	pthread_mutex_unlock(&all->forks[philo->right]);
	++philo->count_eat;
	pthread_mutex_lock(&philo->all->manger);
	if (philo->all->each_must_eat != -1
			&& philo->count_eat == philo->all->each_must_eat)
	{
		pthread_mutex_unlock(&philo->all->manger);
		return (1);
	}
	pthread_mutex_unlock(&philo->all->manger);
	return (0);
}

void				my_sleep(unsigned long itime)
{
	unsigned long	stime;
	unsigned long	ctime;

	stime = get_time();
	while (1)
	{
		ctime = get_time();
		if (ctime - stime >= itime)
			return ;
		usleep(100);
	}
}

int					is_someone_dead(t_philo *philo, unsigned long curr_time)
{
	if (philo->all->est_mort == 1
			|| curr_time - philo->last_eat > philo->all->time_to_die)
		return (1);
	return (0);
}

int print_phrase(t_philo *philo, int status, unsigned long curr_time)
{
	pthread_mutex_lock(&(philo->all->phrase));
	if ((status != DEAD && is_someone_dead(philo, curr_time)))
	{
		pthread_mutex_unlock(&(philo->all->phrase));
		return (1);
	}
	printf("%lums %d", curr_time - philo->all->debut_dinner, philo->pos);
	if (status == TAKE_FORK)
		printf(" has taken a fork\n");
	if (status == EATING)
	{
		printf(" is eating\n");
		philo->last_eat = curr_time;
	}
	if (status == SLEEPING)
		printf(" is sleeping\n");
	if (status == THINKING)
		printf(" is thinking\n");
	if (status == DEAD)
		printf(" died\n");
	pthread_mutex_unlock(&(philo->all->phrase));
	return (0);
}
