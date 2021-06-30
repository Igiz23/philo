#include "philo_bonus.h"

void	*die_check(void *philo)
{
	t_ph	*ph;
	t_all	*res;

	ph = (t_ph *)philo;
	res = ph->res;
	while (1)
	{
		if ((time_ms() - ph->last_eat) >= res->live)
		{
			if (res->eat_count == -1 || res->philo_count == 1)
				write_status(res, ph->id, 'd');
			res->died = 1;
			sem_wait(res->write);
			exit(1);
		}
		if (res->died)
			break ;
		usleep(100);
	}
	return (NULL);
}

void	philo_eats(t_ph *ph, t_all *res)
{
	sem_wait(res->fork);
	write_status(res, ph->id, 'f');
	sem_wait(res->fork);
	write_status(res, ph->id, 'f');
	write_status(res, ph->id, 'e');
	ph->last_eat = time_ms();
	if (res->eat_count > 0 && res->eat_count != ph->eat_now)
	{
		sem_post(res->eat_check);
		(ph->eat_now)++;
	}
	smart_sleep(res->eat, res);
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
	pthread_create(&(ph->die_check), NULL, die_check, philo);
	while (!res->died)
	{
		philo_eats(ph, res);
		if (res->eat_count == ph->eat_now)
			break ;
		write_status(res, ph->id, 's');
		smart_sleep(res->sleep, res);
		write_status(res, ph->id, 't');
	}
	pthread_join(ph->die_check, NULL);
	if (res->died)
		exit(1);
	exit(0);
}
