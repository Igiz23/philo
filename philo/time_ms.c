#include "philo.h"

int	finish_thread(t_all *res)
{
	int	i;

	i = 0;
	while (i < res->philo_count)
	{
		if (pthread_detach(res->ph[i].thread_id) != 0)
			return (exit_error_msg('p'));
		i++;
	}
	i = res->philo_count;
	while (i > -1)
	{
		if (pthread_mutex_destroy(&(res->ph[i].fork)) != 0)
			return (1);
		i--;
	}
	if ((pthread_mutex_destroy(&(res->write)) != 0) || \
		pthread_mutex_destroy(&(res->eat_check)) != 0)
		return (1);
	return (0);
}

int	exit_error_msg(char c)
{
	if (c == 'i')
		ft_putstr_fd(R"Incorrect input data !\n"RS, 2);
	if (c == 'w')
	{
		ft_putstr_fd(R"Wrong number of arguments!\n"RS, 2);
		ft_putstr_fd(Y"Argc == 5 or 6!\n\n"RS, 2);
		ft_putstr_fd(G"[2] - number_of_philosophers\n[3] - time_to_die\n"
			"[4] - time_to_eat\n[5] - time_to_sleep\n"
			"[6] - number_of_times_each_philosopher_must_eat\n"RS, 2);
	}
	if (c == 'p')
		ft_putstr_fd("Pthread error!\n", 2);
	if (c == 'm')
		ft_putstr_fd("Mutex error!\n", 2);
	if (c == 'e')
		ft_putstr_fd("Error!\n", 2);
	if (c == 'n')
		ft_putstr_fd((""), 2);
	return (1);
}

long long	time_ms(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000000 + time.tv_usec) / 1000);
}

void	smart_sleep(long long time, t_all *rules)
{
	long long	i;

	i = time_ms();
	while (!(rules->dieded))
	{
		if ((time_ms() - i) == time)
			break ;
		usleep(10);
	}
}

void	write_status(t_all *rules, int id, char c)
{
	long long	i;

	pthread_mutex_lock(&(rules->write));
	if (!(rules->dieded))
	{
		i = time_ms() - rules->start;
		ft_putnbr_fd(i, 1);
		ft_putchar_fd(' ', 1);
		ft_putnbr_fd(id + 1, 1);
		if (c == 'f')
			ft_putstr_fd(G" has taken a fork"RS, 1);
		if (c == 'e')
			ft_putstr_fd(Y" is eating"RS, 1);
		if (c == 's')
			ft_putstr_fd(" is sleeping", 1);
		if (c == 't')
			ft_putstr_fd(" is thinking", 1);
		if (c == 'd')
			ft_putstr_fd(R" died"RS, 1);
		ft_putchar_fd('\n', 1);
	}
	pthread_mutex_unlock(&(rules->write));
}
