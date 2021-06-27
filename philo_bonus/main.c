#include "philo_bonus.h"

int	main(int argc, char **argv)
{
	t_all	res;

	if (argc == 5 || argc == 6)
	{
		if (parse_arguments(argc, argv))
			return (exit_error_msg('i'));
		if (init_struct(&res, argc, argv))
			return (exit_error_msg('i'));
		if (init_mutex(&res) || init_philo(&res)
			|| init_thread(&res))
			return (exit_error_msg('e'));
		if(finish_thread(&res))
			return (exit_error_msg('n'));
	}
	else
		return (exit_error_msg('w'));
	return (0);
}
