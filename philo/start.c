#include "philo.h"

void	die_check(t_all *res, t_ph *ph)
{
	int	i;

	while (!(res->all_ate))
	{
		i = -1;
		while (++i < res->philo_count && !(res->dieded))
		{
			pthread_mutex_lock(&(res->eat_check));
			if ((time_ms() - ph[i].last_eat) > res->live)
			{
				if (res->eat_count != -1 && res->philo_count != 1)
					res->dieded = 1;
				else
				{
					write_status(res, i, 'd');
					res->dieded = 1;
				}
			}
			pthread_mutex_unlock(&(res->eat_check));
			usleep(100);
		}
		if (res->dieded)
			break ;
//		i = 0;
//		while (res->eat_count != -1 && i < res->philo_count
//			&& ph[i++].x_ate >= res->eat_count)
////			i++;
//		if (i == res->philo_count)
//			res->all_ate = 1;
	}
}

int	init_thread(t_all *res)
{
	int		i;
	t_ph	*philo;

	i = 0;
	philo = res->ph;
	res->start = time_ms();
	while (i < res->philo_count)
	{
		if (pthread_create(&(res->ph[i].thread_id), NULL,
				philo_thread, &(res->ph[i])))
			return (exit_error_msg('p'));
		philo[i].last_eat = time_ms();
		usleep(1000);
		i++;
	}
	die_check(res, res->ph);
	return (0);
}

int	init_philo(t_all *res)
{
	int	i;

	i = res->philo_count;
	res->start = time_ms();
	while (--i > -1)
	{
		res->ph[i].id = i;
		res->ph[i].left = i;
		res->ph[i].right = (i + 1) % res->philo_count;
		res->ph[i].last_eat = 0;
		res->ph[i].eat_now = 0;
		res->ph[i].res = res;
	}
	return (0);
}

int	init_mutex(t_all *res)
{
	int	i;

	i = res->philo_count;
	while (--i > -1)
	{
		if (pthread_mutex_init(&(res->ph[i].fork), NULL))
			return (exit_error_msg('m'));
	}
	if (pthread_mutex_init(&(res->write), NULL) || \
		pthread_mutex_init(&(res->eat_check), NULL))
		return (exit_error_msg('m'));
	return (0);
}

int	init_struct(t_all *res, int argc, char **argv)
{
	res->philo_count = ft_atoi(argv[1]);
	res->live = ft_atoi(argv[2]);
	res->eat = ft_atoi(argv[3]);
	res->sleep = ft_atoi(argv[4]);
	if (res->philo_count < 1 || res->live <= 59 || res->eat <= 59
		|| res->sleep <= 59 || res->philo_count > 200)
		return (1);
	if (argc == 6)
	{
		res->eat_count = ft_atoi(argv[5]);
		if (res->eat_count == 0)
			return (1);
	}
	else
		res->eat_count = -1;
	return (0);
}
