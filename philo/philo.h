#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>

# define R	"\x1b[31m"
# define G	"\x1b[32m"
# define Y	"\x1b[33m"
# define RS	"\x1b[0m"

typedef pthread_mutex_t	t_mutex;

typedef struct s_ph
{
	int				id;
	int				left;
	int				right;
	int				eat_now;
	long long		last_eat;
	int				x_ate;
	int				pid;
	t_mutex			fork;
	pthread_t		thread_id;
	void			*res;

}	t_ph;

typedef struct s_all
{
	int				philo_count;
	long long		start;
	int				live;
	int				eat;
	int				sleep;
	int				eat_count;
	int				dieded;
	int				all_ate;
	t_mutex			write;
	t_mutex			eat_check;
	struct s_ph		ph[200];
}	t_all;
int					exit_error_msg(char c);
void				ft_putstr_fd(char *s, int fd);
int					ft_strlen(const char *s);
int					ft_isdigit(int c);
int					ft_atoi(const char *str);
void				ft_putnbr_fd(long long n, int fd);
void				ft_putchar_fd(char c, int fd);

int					parse_arguments(int argc, char **argv);
int					init_struct(t_all *res, int argc, char **argv);
long long			time_ms(void);
void				*philo_thread(void *philo);
void				smart_sleep(long long time, t_all *res);
void				write_status(t_all *rules, int id, char c);
int					init_thread(t_all *res);
int					init_philo(t_all *res);
int					init_mutex(t_all *res);
int					finish_thread(t_all *res);

#endif