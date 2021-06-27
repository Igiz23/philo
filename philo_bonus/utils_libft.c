#include "philo.h"

void	ft_putstr_fd(char *s, int fd)
{
	if (s != 0)
		write(fd, s, ft_strlen(s));
}

int	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		i++;
	}
	return (i);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

int	ft_is_space(int c)
{
	return (c == ' ' || c == '\t' || c == '\f' || \
	 c == '\r' || c == '\n' || c == '\v');
}

int	ft_atoi(const char *str)
{
	long int	num;
	int			i;
	int			zn;
	long int	o;

	o = 922337203685477580;
	zn = 1;
	i = 0;
	num = 0;
	while (ft_is_space(str[i]))
		i++;
	if (str[i] == '-')
		zn = -1;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i] >= '0' && '9' >= str[i])
	{
		if ((num > o && zn == 1) || (num == o && str[i] > '7' && zn == 1))
			return (-1);
		if ((num > o && zn == -1) || (num == o && str[i] > '8' && zn == -1 ))
			return (0);
		num = (num * 10) + (str[i] - '0');
		i++;
	}
	return (zn * num);
}
