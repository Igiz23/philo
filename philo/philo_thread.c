#include "philo.h"

void	philo_eats(t_ph *ph, t_all *res)
{
	pthread_mutex_lock(&(res->ph[ph->left].fork));
	write_status(res, ph->id, 'f');
	pthread_mutex_lock(&(res->ph[ph->right].fork));
	write_status(res, ph->id, 'f');
	write_status(res, ph->id, 'e');
	ph->last_eat = time_ms();
	smart_sleep(res->eat, res);
	(ph->eat_now)++;
	pthread_mutex_unlock(&(res->ph[ph->left].fork));
	pthread_mutex_unlock(&(res->ph[ph->right].fork));
}

void	*philo_thread(void *philo)
{
	t_ph	*ph;
	t_all	*res;

	ph = (t_ph *)philo;
	res = ph->res;
	if (ph->id % 2)
		usleep(1000);
	while (!(res->died))
	{
		philo_eats(ph, res);
		if (res->eat_count == ph->eat_now)
			break ;
		write_status(res, ph->id, 's');
		smart_sleep(res->sleep, res);
		write_status(res, ph->id, 't');
	}
	return (NULL);
}
