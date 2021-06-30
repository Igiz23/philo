#include "philo_bonus.h"

int	init_sem(t_all *res)
{
	sem_unlink("ph_eat");
	sem_unlink("ph_fork");
	sem_unlink("ph_eat_check");
	res->fork = sem_open("ph_fork", O_CREAT, S_IRWXU, res->philo_count);
	res->write = sem_open("ph_write", O_CREAT, S_IRWXU, 1);
	res->eat_check = sem_open("ph_eat_check", O_CREAT, S_IRWXU, 0);
	if (res->fork <= 0 || res->write <= 0 || res->eat_check <= 0)
		return (1);
	return (0);
}

void	*check_eat(void *rest)
{
	t_all	*res;

	res = rest;
	while (res->eat_count > 0 && res->eat_new <= \
	res->eat_count * res->philo_count)
	{
		sem_wait(res->eat_check);
		res->eat_new++;
	}
	return (NULL);
}

int	init_process(t_all *res)
{
	int		i;
	t_ph	*philo;

	i = 0;
	philo = res->ph;
	res->start = time_ms();
	pthread_create(&(res->eat_th), NULL, check_eat, philo);
	while (i < res->philo_count)
	{
		res->ph[i].pid = fork();
		if (res->ph[i].pid < 0)
			return (exit_error_msg('f'));
		if (res->ph[i].pid == 0)
		{
			philo_thread(&(philo[i]));
			usleep(1000);
		}
		i++;
	}
	pthread_join(res->eat_th, NULL);
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
		res->ph[i].last_eat = 0;
		res->ph[i].eat_now = 0;
		res->ph[i].res = res;
	}
	return (0);
}

int	init_struct(t_all *res, int argc, char **argv)
{
	res->philo_count = ft_atoi(argv[1]);
	res->live = ft_atoi(argv[2]);
	res->eat = ft_atoi(argv[3]);
	res->sleep = ft_atoi(argv[4]);
	res->died = 0;
	if (res->philo_count < 1 || res->live <= 59 || res->eat <= 59
		|| res->sleep <= 59 || res->philo_count > 200)
		return (1);
	if (argc == 6)
		res->eat_count = ft_atoi(argv[5]);
	else
		res->eat_count = -1;
	return (0);
}
