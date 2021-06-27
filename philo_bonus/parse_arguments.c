#include "philo.h"

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void	ft_putnbr_fd(long long n, int fd)
{
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		ft_putnbr_fd(-n, fd);
	}
	else if (n > 9)
	{
		ft_putnbr_fd(n / 10, fd);
		ft_putchar_fd(n % 10 + '0', fd);
	}
	else
		ft_putchar_fd(n + '0', fd);
}

static int	check_digit(char *str, int len, int flags)
{
	int	i;

	i = 0;
	if (flags == 1)
	{
		i = 1;
		while (i != len)
		{
			if (!ft_isdigit(str[i]))
				return (1);
			i++;
		}
	}
	else
	{
		while (i != len)
		{
			if (!ft_isdigit(str[i]))
				return (1);
			i++;
		}
	}
	return (0);
}

static int	check_int(char *str)
{
	int	i;
	int	len;
	int	flags;

	i = 0;
	len = ft_strlen(str);
	flags = 0;
	if (str[i] == '+')
	{
		flags = 1;
		if (len == 1)
			return (1);
		if (check_digit(str, len, flags))
			return (1);
	}
	else if (check_digit(str, len, flags))
		return (1);
	return (0);
}

int	parse_arguments(int argc, char **argv)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (check_int(argv[i]))
			return (1);
		i++;
	}
	return (0);
}
