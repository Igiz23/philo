#include "philo_bonus.h"

void	philo_eats(t_ph *ph, t_all *res)
{
	sem_wait(res->fork);
	sem_wait(res->fork);
	write_status(res, ph->id, 'f');
	sem_wait(res->eat_check);
	write_status(res, ph->id, 'e');
	ph->last_eat = time_ms();
	sem_post(res->eat_check);
	smart_sleep(res->sleep, res);
	(ph->eat_now)++;
	sem_post(res->fork);
	sem_post(res->fork);
}

void	philo_thread(void *philo)
{
	t_ph	*ph;
	t_all	*res;

	ph = (t_ph *)philo;
	res = ph->res;
	ph->last_eat = time_ms();
	pthread_create(&(ph->die_check), NULL,  die_check, philo);
	if (ph->id % 2)
		usleep(1500);
	while (!res->dieded)
	{
		philo_eats(ph, res);
		if (res->eat_count == ph->eat_now)
			break ;
		write_status(res, ph->id, 's');
		smart_sleep(res->sleep, res);
		write_status(res, ph->id, 't');
	}
	pthread_join(ph->die_check, NULL);
	if (res->dieded)
		exit(1);
	exit(0);
}
