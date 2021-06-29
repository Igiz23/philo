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
		if (init_philo(&res))
			return (exit_error_msg('e'));
		if (init_sem(&res))
			return (exit_error_msg('e'));
		init_process(&res);
		finish_process(&res);
	}
	else
		return (exit_error_msg('w'));
	return (0);
}
