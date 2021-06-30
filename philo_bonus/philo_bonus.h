#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <signal.h>
# include <semaphore.h>

# define R	"\x1b[31m"
# define G	"\x1b[32m"
# define Y	"\x1b[33m"
# define RS	"\x1b[0m"

typedef struct s_ph
{
	int				id;
	int				eat_now;
	long long		last_eat;
	pid_t			pid;
	pthread_t		die_check;
	struct s_all	*res;

}	t_ph;

typedef struct s_all
{
	int				philo_count;
	long long		start;
	int				live;
	int				eat;
	int				sleep;
	int				eat_new;
	int				eat_count;
	int				died;
	sem_t			*write;
	sem_t			*fork;
	sem_t			*eat_check;
	pthread_t		eat_th;
	struct s_ph		ph[215];
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
void				*die_check(void *philo);
void				philo_thread(void *philo);
void				smart_sleep(long long time, t_all *res);
void				write_status(t_all *rules, int id, char c);
int					init_process(t_all *res);
int					init_sem(t_all *res);
int					init_philo(t_all *res);
int					finish_process (t_all *res);

#endif