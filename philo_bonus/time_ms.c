#include "philo_bonus.h"

int	finish_process(t_all *res)
{
	int	i;

	i = 0;
	waitpid(-1, 0, 0);
	while (i < res->philo_count)
	{
		kill(res->ph[i].pid, SIGKILL);
		i++;
	}
	sem_close(res->write);
	sem_close(res->fork);
	sem_close(res->eat_check);
	sem_unlink("ph_fork");
	sem_unlink("ph_write");
	sem_unlink("ph_eat_check");
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
	if (c == 'f')
		ft_putstr_fd("Forks error!\n", 2);
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
	while (!(rules->died))
	{
		if ((time_ms() - i) >= time)
			break ;
		usleep(50);
	}
}

void	write_status(t_all *rules, int id, char c)
{
	long long	i;

	sem_wait(rules->write);
	if (!(rules->died))
	{
		i = time_ms() - rules->start;
		ft_putnbr_fd(i, 1);
		ft_putchar_fd(' ', 1);
		ft_putnbr_fd(id + 1, 1);
		if (c == 'f')
			ft_putstr_fd(G" has taken a fork\n"RS, 2);
		if (c == 'e')
			ft_putstr_fd(Y" is eating\n"RS, 2);
		if (c == 's')
			ft_putstr_fd(" is sleeping\n", 2);
		if (c == 't')
			ft_putstr_fd(" is thinking\n", 2);
		if (c == 'd')
		{
			ft_putstr_fd(R" died\n"RS, 2);
			exit (0);
		}
	}
	sem_post(rules->write);
	return ;
}
