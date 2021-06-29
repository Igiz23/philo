#include "philo_bonus.h"

void	*die_check(void *philo)
{
	t_ph	*ph;
	t_all	*res;

	ph = (t_ph *)philo;
	res = ph->res;
	while (1)
	{
		sem_wait(res->eat_check);
		if ((time_ms() - ph->last_eat) >= res->live)
		{
			write_status(res, ph->id, 'd');
			res->dieded = 1;
			sem_wait(res->write);
			exit(1);
		}
		sem_post(res->eat_check);
		if (res->dieded)
			break;
		usleep(100);
		if (res->eat_count != -1 && ph->eat_now >= res->eat_count)
			break;
	}
	return (NULL);
}
int	init_sem(t_all *res)
{
	sem_unlink("/ph_fork");
	sem_unlink("/ph_write");
	sem_unlink("/ph_eat_check");
	res->fork = sem_open("/ph_fork", O_CREAT, S_IRWXU, res->philo_count);
	res->write = sem_open("/ph_write", O_CREAT, S_IRWXU, 1);
	res->eat_check = sem_open("/ph_eat_check", O_CREAT, S_IRWXU, 1);
	if (res->fork <= 0 || res->write <= 0 || res->eat_check <= 0)
		return (1);
	return (0);
}
int	init_process(t_all *res)
{
	int		i;
	t_ph	*philo;

	i = 0;
	philo = res->ph;
	res->start = time_ms();
	while (i < res->philo_count)
	{
		res->ph[i].pid = fork();
		if(res->ph[i].pid < 0)
			return (exit_error_msg('f'));
		if(res->ph[i].pid == 0)
		{
			philo_thread(&(philo[i]));
			usleep(200);
		}
		i++;
	}
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
	res->dieded = 0;
	if (res->philo_count < 1 || res->live <= 59 || res->eat <= 59
		|| res->sleep <= 59 || res->philo_count > 200)
		return (1);
	if (argc == 6)
		res->eat_count = ft_atoi(argv[5]);
	else
		res->eat_count = -1;
	return (0);
}