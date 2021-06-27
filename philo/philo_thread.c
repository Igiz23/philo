#include "philo.h"

void	philo_eats(t_ph *ph, t_all *res)
{
	pthread_mutex_lock(&(res->ph[ph->left].fork));
	pthread_mutex_lock(&(res->ph[ph->right].fork));
	write_status(res, ph->id, 'f');
	pthread_mutex_lock(&(res->eat_check));
	write_status(res, ph->id, 'e');
	ph->last_eat = time_ms();
	pthread_mutex_unlock(&(res->eat_check));
	smart_sleep(res->sleep, res);
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
		usleep(200);
	while (1)
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
